#pragma once
#include "TestCollector.h"
#include "Game/Protocol/GameProtocol.h"
#include "Game/GameConfigurationProvider.h"
#include "Game/GameEngine.h"

class GameEngineTests
    : public QObject
{
    Q_OBJECT

public:
    GameEngineTests();
    virtual ~GameEngineTests();

private slots:
    void CreatesWithGeneratedId();
    void CreatedGameIsValid();
    void NonExistingGameIsInvalid();
    void BuildsWall();
    void DoesNotUpdateInvalidGame();
    void ValidGameIsProperlyUpdated();
    void ChangeLogIsGeneratedForZombieMovement();
    void GameIsLostWhenZombieReachesTheWall();
    void ChangeLogForSuccessfullAttackIsGenerated();
    void ChangeLogForFailureAttackIsGenerated();
    void ZombieCanBeKilledOnceOnTheSamePosition();
    void GameIsWonAfterTenZombiesAreKilled();
    void EngineMovesAllZombiesUpwardsWhenRequested();
    void EngineCreatesNewZombieAtEmptyBottomSpot();
    void NewNumberOfZombiesIsCorrect();
    void EngineNotifiesAboutZombieMovementsAndCreation();
    void BuildsWallForSpecifiedBoardSize();
    void GameIsWonAfterSpecifiedAmountOfZombiesAreKilled();

private:
    std::unique_ptr<Game::Protocol::GameProtocol> m_protocol;
    std::unique_ptr<Game::GameConfigurationProvider> m_gameConfigurationProvider;
    std::unique_ptr<Game::GameEngine> m_engine;
};
ADD_TEST(GameEngineTests)
