#include "GameConfigurationProviderTests.h"

GameConfigurationProviderTests::GameConfigurationProviderTests()
{
}

GameConfigurationProviderTests::~GameConfigurationProviderTests()
{
}

void GameConfigurationProviderTests::EverythingIsZeroByDefault()
{
    // Arrange
    Game::GameConfigurationProvider provider;

    // Assert
    QVERIFY(0 == provider.GetColumns());
    QVERIFY(0 == provider.GetRows());
    QVERIFY(0 == provider.GetZombiesToKill());
}

void GameConfigurationProviderTests::ColumnsCanBeSet()
{
    // Arrange
    Game::GameConfigurationProvider provider;

    // Act
    provider.SetColumns(10);

    // Assert
    QVERIFY(10 == provider.GetColumns());
}

void GameConfigurationProviderTests::RowsCanBeSet()
{
    // Arrange
    Game::GameConfigurationProvider provider;

    // Act
    provider.SetRows(10);

    // Assert
    QVERIFY(10 == provider.GetRows());
}

void GameConfigurationProviderTests::ZombiesToKillCanBeSet()
{
    // Arrange
    Game::GameConfigurationProvider provider;

    // Act
    provider.SetZombiesToKill(10);

    // Assert
    QVERIFY(10 == provider.GetZombiesToKill());
}

void GameConfigurationProviderTests::EverythingCanBeSet()
{
    // Arrange
    Game::GameConfigurationProvider provider;

    // Act
    provider.SetColumns(10);
    provider.SetRows(11);
    provider.SetZombiesToKill(12);

    // Assert
    QVERIFY(10 == provider.GetColumns());
    QVERIFY(11 == provider.GetRows());
    QVERIFY(12 == provider.GetZombiesToKill());
}

void GameConfigurationProviderTests::GameUpdateTimeIsZeroInitially()
{
    // Arrange
    Game::GameConfigurationProvider provider;

    // Assert
    QVERIFY(0 == provider.GetGameUpdateTime());
}

void GameConfigurationProviderTests::GameUpdateTimeCanBeSet()
{
    // Arrange
    Game::GameConfigurationProvider provider;

    // Act
    provider.SetGameUpdateTime(1000);

    // Assert
    QVERIFY(1000 == provider.GetGameUpdateTime());
}
