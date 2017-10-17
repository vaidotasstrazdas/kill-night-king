#include "GameTests.h"

GameTests::GameTests()
{
}

GameTests::~GameTests()
{
}

void GameTests::EmptyGameIsInvalidByDefault()
{
    // Arrange
    Game::Model::Game game;

    // Assert
    QVERIFY(!game.IsValid());
}

void GameTests::GameBecomesValidWhenUnitIsInserted()
{
    // Arrange
    Game::Model::Game game;

    // Act
    game.InsertUnit(Game::Model::GameUnit { Game::Model::Point(0, 0), Game::Model::GameUnitType::Archer });

    // Assert
    QVERIFY(game.IsValid());
}

void GameTests::GetsUnitBySpecifiedPoint()
{
    // Arrange
    Game::Model::Game game;
    game.InsertUnit(Game::Model::GameUnit { Game::Model::Point(30, 60), Game::Model::GameUnitType::Archer });

    // Act
    const auto unit = game.GetUnit(Game::Model::Point(30, 60));

    // Assert
    QVERIFY(30 == unit.m_point.m_x);
    QVERIFY(60 == unit.m_point.m_y);
    QVERIFY(Game::Model::GameUnitType::Archer == unit.m_type);
}

void GameTests::GameIsNotLostInitially()
{
    // Arrange
    Game::Model::Game game;

    // Assert
    QVERIFY(!game.GameIsLost());
}

void GameTests::GameCanBeLost()
{
    // Arrange
    Game::Model::Game game;

    // Act
    game.LoseGame();

    // Assert
    QVERIFY(game.GameIsLost());
}

void GameTests::GameIsNotWonInitially()
{
    // Arrange
    Game::Model::Game game;

    // Assert
    QVERIFY(!game.GameIsWon());
}

void GameTests::GameCanBeWon()
{
    // Arrange
    Game::Model::Game game;

    // Act
    game.WinGame();

    // Assert
    QVERIFY(game.GameIsWon());
}
