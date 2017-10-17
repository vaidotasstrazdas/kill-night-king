#include <QString>
#include <QtTest>
#include <qdebug.h>

#include "GameEngineTests.h"

GameEngineTests::GameEngineTests()
    : m_protocol(new Game::Protocol::GameProtocol())
    , m_gameConfigurationProvider(new Game::GameConfigurationProvider())
    , m_engine(new Game::GameEngine(*m_protocol, *m_gameConfigurationProvider))
{
    m_gameConfigurationProvider->SetColumns(30);
    m_gameConfigurationProvider->SetRows(30);
    m_gameConfigurationProvider->SetZombiesToKill(10);
}

GameEngineTests::~GameEngineTests()
{
}

void GameEngineTests::CreatesWithGeneratedId()
{
    // Act & Assert
    QVERIFY("" != m_engine->CreateGame());
}

void GameEngineTests::CreatedGameIsValid()
{
    // Arrange
    const auto gameId = m_engine->CreateGame();

    // Act
    auto& game = m_engine->GetGame(gameId);

    // Assert
    QVERIFY(game.IsValid());
}

void GameEngineTests::NonExistingGameIsInvalid()
{
    // Act
    auto& game = m_engine->GetGame("Non Existing Game Id");

    // Assert
    QVERIFY(!game.IsValid());
}

void GameEngineTests::BuildsWall()
{
    // Arrange
    const unsigned int columns = 30;
    const auto gameId = m_engine->CreateGame();

    // Act
    auto& game = m_engine->GetGame(gameId);

    // Assert
    for (unsigned int x = 0; x < columns; x++)
    {
        const auto point = Game::Model::Point(x, 0);
        QVERIFY(Game::Model::GameUnitType::Wall == game.GetUnit(point).m_type);
    }
}

void GameEngineTests::DoesNotUpdateInvalidGame()
{
    // Assert
    QVERIFY(!m_engine->UpdateGame("Non Existing Game Id", "some data"));
}


void GameEngineTests::ValidGameIsProperlyUpdated()
{
    // Arrange
    const auto gameId = m_engine->CreateGame();
    m_engine->GetGame(gameId).InsertUnit(Game::Model::GameUnit(Game::Model::Point(0, 29), Game::Model::GameUnitType::Zombie));

    // Act & Assert
    QVERIFY(m_engine->UpdateGame(gameId, "M0,29;0,28\n"));
}

void GameEngineTests::GameIsLostWhenZombieReachesTheWall()
{
    // Arrange
    const auto gameId = m_engine->CreateGame();
    auto& game = m_engine->GetGame(gameId);
    game.InsertUnit(Game::Model::GameUnit(Game::Model::Point(0, 29), Game::Model::GameUnitType::Zombie));

    // Act
    m_engine->UpdateGame(gameId, "M0,29;0,0\n");

    // Assert
    const auto changeLog = m_engine->GetChangeLog(gameId);
    QVERIFY(1 == changeLog.size());
    QVERIFY("Zombie has reached the wall!!! Westeros is DOOMED!!! You have LOST!!!" == changeLog[0]);
    QVERIFY(game.GameIsLost());
}

void GameEngineTests::ChangeLogIsGeneratedForZombieMovement()
{
    // Arrange
    const auto gameId = m_engine->CreateGame();
    m_engine->GetGame(gameId).InsertUnit(Game::Model::GameUnit(Game::Model::Point(0, 29), Game::Model::GameUnitType::Zombie));

    // Act
    m_engine->UpdateGame(gameId, "M0,29;0,28\n");

    // Assert
    const auto changeLog = m_engine->GetChangeLog(gameId);
    QVERIFY(1 == changeLog.size());
    QVERIFY("Zombie moved from (0, 29) to (0, 28)" == changeLog[0]);
}

void GameEngineTests::ChangeLogForSuccessfullAttackIsGenerated()
{
    // Arrange
    const auto gameId = m_engine->CreateGame();
    m_engine->GetGame(gameId).InsertUnit(Game::Model::GameUnit(Game::Model::Point(0, 29), Game::Model::GameUnitType::Zombie));

    // Act
    m_engine->UpdateGame(gameId, "A0,0;0,29\n");

    // Assert
    const auto changeLog = m_engine->GetChangeLog(gameId);
    QVERIFY(1 == changeLog.size());
    QVERIFY("Your glorious archers killed the zombie at (0, 29)! Congratz, pal!" == changeLog[0]);
}

void GameEngineTests::ChangeLogForFailureAttackIsGenerated()
{
    // Arrange
    const auto gameId = m_engine->CreateGame();
    m_engine->GetGame(gameId).InsertUnit(Game::Model::GameUnit(Game::Model::Point(0, 28), Game::Model::GameUnitType::Zombie));

    // Act
    m_engine->UpdateGame(gameId, "A0,0;0,29\n");

    // Assert
    const auto changeLog = m_engine->GetChangeLog(gameId);
    QVERIFY(1 == changeLog.size());
    QVERIFY("There are no zombies at (0, 29)! Look where shooting!!! Don't you see Westeros is in danger?!!" == changeLog[0]);
}

void GameEngineTests::ZombieCanBeKilledOnceOnTheSamePosition()
{
    // Arrange
    const auto gameId = m_engine->CreateGame();
    m_engine->GetGame(gameId).InsertUnit(Game::Model::GameUnit(Game::Model::Point(0, 29), Game::Model::GameUnitType::Zombie));

    // Act
    m_engine->UpdateGame(gameId, "A0,0;0,29\nA0,0;0,29\n");

    // Assert
    const auto changeLog = m_engine->GetChangeLog(gameId);
    QVERIFY(2 == changeLog.size());
    QVERIFY("Your glorious archers killed the zombie at (0, 29)! Congratz, pal!" == changeLog[0]);
    QVERIFY("There are no zombies at (0, 29)! Look where shooting!!! Don't you see Westeros is in danger?!!" == changeLog[1]);
}

void GameEngineTests::GameIsWonAfterTenZombiesAreKilled()
{
    // Arrange
    const auto gameId = m_engine->CreateGame();
    auto& game = m_engine->GetGame(gameId);
    std::string killSequence = "";
    for (unsigned int x = 0; x < 10; x++)
    {
        game.InsertUnit(Game::Model::GameUnit(Game::Model::Point(x, 29), Game::Model::GameUnitType::Zombie));
        killSequence += "A0,0;" + std::to_string(x) + ",29\n";
    }

    // Act
    m_engine->UpdateGame(gameId, killSequence);

    // Assert
    const auto changeLog = m_engine->GetChangeLog(gameId);
    QVERIFY(11 == changeLog.size());
    QVERIFY("Your glorious archers killed the zombie at (0, 29)! Congratz, pal!" == changeLog[0]);
    QVERIFY("Your glorious archers killed the zombie at (1, 29)! Congratz, pal!" == changeLog[1]);
    QVERIFY("Your glorious archers killed the zombie at (2, 29)! Congratz, pal!" == changeLog[2]);
    QVERIFY("Your glorious archers killed the zombie at (3, 29)! Congratz, pal!" == changeLog[3]);
    QVERIFY("Your glorious archers killed the zombie at (4, 29)! Congratz, pal!" == changeLog[4]);
    QVERIFY("Your glorious archers killed the zombie at (5, 29)! Congratz, pal!" == changeLog[5]);
    QVERIFY("Your glorious archers killed the zombie at (6, 29)! Congratz, pal!" == changeLog[6]);
    QVERIFY("Your glorious archers killed the zombie at (7, 29)! Congratz, pal!" == changeLog[7]);
    QVERIFY("Your glorious archers killed the zombie at (8, 29)! Congratz, pal!" == changeLog[8]);
    QVERIFY("Your glorious archers killed the zombie at (9, 29)! Congratz, pal!" == changeLog[9]);
    QVERIFY("Night King pissed poorly and ran away from your glorious troops! Westeros is saved! At least for now..." == changeLog[10]);
    QVERIFY(game.GameIsWon());
}

void GameEngineTests::EngineMovesAllZombiesUpwardsWhenRequested()
{
    // Arrange
    const auto gameId = m_engine->CreateGame();
    auto& game = m_engine->GetGame(gameId);

    for (unsigned int x = 0; x < 10; x++)
        game.InsertUnit(Game::Model::GameUnit(Game::Model::Point(x, 29), Game::Model::GameUnitType::Zombie));

    // Act
    m_engine->UpdateGameAutomatically(gameId);

    // Assert
    for (unsigned int x = 0; x < 10; x++)
    {
        const auto gameUnit = game.GetUnit(Game::Model::Point(x, 28));
        QVERIFY(Game::Model::GameUnitType::Zombie == gameUnit.m_type);
    }
}

void GameEngineTests::EngineCreatesNewZombieAtEmptyBottomSpot()
{
    // Arrange
    const auto gameId = m_engine->CreateGame();
    auto& game = m_engine->GetGame(gameId);

    for (unsigned int x = 0; x < 10; x++)
        game.InsertUnit(Game::Model::GameUnit(Game::Model::Point(x, 29), Game::Model::GameUnitType::Zombie));

    // Act
    m_engine->UpdateGameAutomatically(gameId);

    // Assert
    const auto gameUnit = game.GetUnit(Game::Model::Point(0, 29));
    QVERIFY(Game::Model::GameUnitType::Zombie == gameUnit.m_type);
}

void GameEngineTests::NewNumberOfZombiesIsCorrect()
{
    // Arrange
    const auto gameId = m_engine->CreateGame();
    auto& game = m_engine->GetGame(gameId);

    for (unsigned int x = 0; x < 10; x++)
        game.InsertUnit(Game::Model::GameUnit(Game::Model::Point(x, 29), Game::Model::GameUnitType::Zombie));

    // Act
    m_engine->UpdateGameAutomatically(gameId);

    // Assert
    QVERIFY(11 == game.GetAll([](const Game::Model::GameUnit& unit)
    {
        return unit.m_type == Game::Model::GameUnitType::Zombie;
    }).size());
}

void GameEngineTests::EngineNotifiesAboutZombieMovementsAndCreation()
{
    // Arrange
    const auto gameId = m_engine->CreateGame();
    auto& game = m_engine->GetGame(gameId);

    for (unsigned int x = 0; x < 10; x++)
        game.InsertUnit(Game::Model::GameUnit(Game::Model::Point(x, 29), Game::Model::GameUnitType::Zombie));

    // Act
    m_engine->UpdateGameAutomatically(gameId);

    // Assert
    const auto changeLog = m_engine->GetChangeLog(gameId);
    QVERIFY(11 == changeLog.size());
    QVERIFY("Zombie moved from (0, 29) to (0, 28)" == changeLog[0]);
    QVERIFY("Zombie moved from (1, 29) to (1, 28)" == changeLog[1]);
    QVERIFY("Zombie moved from (2, 29) to (2, 28)" == changeLog[2]);
    QVERIFY("Zombie moved from (3, 29) to (3, 28)" == changeLog[3]);
    QVERIFY("Zombie moved from (4, 29) to (4, 28)" == changeLog[4]);
    QVERIFY("Zombie moved from (5, 29) to (5, 28)" == changeLog[5]);
    QVERIFY("Zombie moved from (6, 29) to (6, 28)" == changeLog[6]);
    QVERIFY("Zombie moved from (7, 29) to (7, 28)" == changeLog[7]);
    QVERIFY("Zombie moved from (8, 29) to (8, 28)" == changeLog[8]);
    QVERIFY("Zombie moved from (9, 29) to (9, 28)" == changeLog[9]);
    QVERIFY("Zombie has appeared at (0, 29)." == changeLog[10]);
}

void GameEngineTests::BuildsWallForSpecifiedBoardSize()
{
    // Arrange
    const unsigned int columns = 300;
    m_gameConfigurationProvider->SetColumns(columns);
    const auto gameId = m_engine->CreateGame();

    // Act
    auto& game = m_engine->GetGame(gameId);

    // Assert
    for (unsigned int x = 0; x < columns; x++)
    {
        const auto point = Game::Model::Point(x, 0);
        QVERIFY(Game::Model::GameUnitType::Wall == game.GetUnit(point).m_type);
    }
}

void GameEngineTests::GameIsWonAfterSpecifiedAmountOfZombiesAreKilled()
{
    // Arrange
    m_gameConfigurationProvider->SetZombiesToKill(5);
    const auto gameId = m_engine->CreateGame();
    auto& game = m_engine->GetGame(gameId);
    std::string killSequence = "";
    for (unsigned int x = 0; x < 5; x++)
    {
        game.InsertUnit(Game::Model::GameUnit(Game::Model::Point(x, 29), Game::Model::GameUnitType::Zombie));
        killSequence += "A0,0;" + std::to_string(x) + ",29\n";
    }

    // Act
    m_engine->UpdateGame(gameId, killSequence);

    // Assert
    const auto changeLog = m_engine->GetChangeLog(gameId);
    QVERIFY(6 == changeLog.size());
    QVERIFY("Your glorious archers killed the zombie at (0, 29)! Congratz, pal!" == changeLog[0]);
    QVERIFY("Your glorious archers killed the zombie at (1, 29)! Congratz, pal!" == changeLog[1]);
    QVERIFY("Your glorious archers killed the zombie at (2, 29)! Congratz, pal!" == changeLog[2]);
    QVERIFY("Your glorious archers killed the zombie at (3, 29)! Congratz, pal!" == changeLog[3]);
    QVERIFY("Your glorious archers killed the zombie at (4, 29)! Congratz, pal!" == changeLog[4]);
    QVERIFY("Night King pissed poorly and ran away from your glorious troops! Westeros is saved! At least for now..." == changeLog[5]);
    QVERIFY(game.GameIsWon());
}
