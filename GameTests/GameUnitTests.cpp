#include "GameUnitTests.h"

GameUnitTests::GameUnitTests()
{
}

GameUnitTests::~GameUnitTests()
{
}

void GameUnitTests::IsInvalidByDefault()
{
    // Arrange
    Game::Model::GameUnit unit;

    // Assert
    QVERIFY(!unit.IsValid());
}

void GameUnitTests::IsValidWhenTypeIsKnown()
{
    // Arrange
    Game::Model::GameUnit unit;
    unit.m_type = Game::Model::GameUnitType::Archer;

    // Assert
    QVERIFY(unit.IsValid());
}

void GameUnitTests::DefaultPointIsZero()
{
    // Arrange
    Game::Model::GameUnit unit;

    // Assert
    QVERIFY(0 == unit.m_point.m_x);
    QVERIFY(0 == unit.m_point.m_y);
}

