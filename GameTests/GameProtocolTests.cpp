#include "GameProtocolTests.h"

GameProtocolTests::GameProtocolTests()
{
}

GameProtocolTests::~GameProtocolTests()
{
}

void GameProtocolTests::ResolvesNoActionForEmptyString()
{
    // Arrange
    Game::Protocol::GameProtocol protocol;

    // Assert
    QVERIFY(protocol.ResolveActions("").empty());
}

void GameProtocolTests::ResolvesSingleMovementAction()
{
    // Arrange
    Game::Protocol::GameProtocol protocol;

    // Act
    auto actions = protocol.ResolveActions("M0,123;0,122\n");

    // Assert
    QVERIFY(1 == actions.size());

    const auto& action = actions.at(0);
    QVERIFY(Game::Protocol::GameActionType::Move == action.m_type);
    QVERIFY(Game::Model::Point(0, 123) == action.m_activator);
    QVERIFY(Game::Model::Point(0, 122) == action.m_affected);
}

void GameProtocolTests::ResolvesActionsLineByLine()
{
    // Arrange
    Game::Protocol::GameProtocol protocol;

    // Act
    auto actions = protocol.ResolveActions("M0,123;0,122\nM0,122;1,121\n");

    // Assert
    QVERIFY(2 == actions.size());

    const auto& actionOne = actions.at(0);
    QVERIFY(Game::Protocol::GameActionType::Move == actionOne.m_type);
    QVERIFY(Game::Model::Point(0, 123) == actionOne.m_activator);
    QVERIFY(Game::Model::Point(0, 122) == actionOne.m_affected);

    const auto& actionTwo = actions.at(1);
    QVERIFY(Game::Protocol::GameActionType::Move == actionTwo.m_type);
    QVERIFY(Game::Model::Point(0, 122) == actionTwo.m_activator);
    QVERIFY(Game::Model::Point(1, 121) == actionTwo.m_affected);
}

void GameProtocolTests::ResolvesAttackAction()
{
    // Arrange
    Game::Protocol::GameProtocol protocol;

    // Act
    auto actions = protocol.ResolveActions("A0,0;1,1\n");

    // Assert
    QVERIFY(1 == actions.size());

    const auto& actionOne = actions.at(0);
    QVERIFY(Game::Protocol::GameActionType::Attack == actionOne.m_type);
    QVERIFY(Game::Model::Point(0, 0) == actionOne.m_activator);
    QVERIFY(Game::Model::Point(1, 1) == actionOne.m_affected);
}
