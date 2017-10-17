#include "GameActionTests.h"

GameActionTests::GameActionTests()
{
}

GameActionTests::~GameActionTests()
{
}

void GameActionTests::DefaultActionIsUnknownWithZeroPoint()
{
    // Arrange
    Game::Protocol::GameAction action;

    // Assert
    QVERIFY(Game::Protocol::GameActionType::Unknown == action.m_type);
    QVERIFY(Game::Model::Point(0, 0) == action.m_activator);
    QVERIFY(Game::Model::Point(0, 0) == action.m_affected);
}

void GameActionTests::CanCreateActionOfSpecifiedTypeAndAffectedPoint()
{
    // Arrange
    Game::Protocol::GameAction action(Game::Protocol::GameActionType::Move, Game::Model::Point(123, 321), Game::Model::Point(456, 654));

    // Assert
    QVERIFY(Game::Protocol::GameActionType::Move == action.m_type);
    QVERIFY(Game::Model::Point(123, 321) == action.m_activator);
    QVERIFY(Game::Model::Point(456, 654) == action.m_affected);
}
