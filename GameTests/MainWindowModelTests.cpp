#include <QSignalSpy>

#include "MainWindowModelTests.h"

MainWindowModelTests::MainWindowModelTests()
{
}

MainWindowModelTests::~MainWindowModelTests()
{
}

void MainWindowModelTests::SetsInitialValues()
{
    // Arrange
    Game::GameConfigurationProvider gameConfigurationProvider;
    Server::ServerMock server;
    Views::MainWindowModel model(server, gameConfigurationProvider);

    // Assert
    QVERIFY(0 == model.GetColumns().GetValue());
    QVERIFY(0 == model.GetRows().GetValue());
    QVERIFY(0 == model.GetPort().GetValue());
    QVERIFY(0 == model.GetZombiesToKill().GetValue());
}

void MainWindowModelTests::ConfiguresGame()
{
    // Arrange
    Game::GameConfigurationProvider gameConfigurationProvider;
    Server::ServerMock server;
    Views::MainWindowModel model(server, gameConfigurationProvider);

    // Act
    model.GetColumns() = 10;
    model.GetRows() = 30;
    model.GetZombiesToKill() = 90;
    model.ConfigureGame();

    // Assert
    QVERIFY(10 == gameConfigurationProvider.GetColumns());
    QVERIFY(30 == gameConfigurationProvider.GetRows());
    QVERIFY(90 == gameConfigurationProvider.GetZombiesToKill());
}

void MainWindowModelTests::StartsServerToListenToSpecifiedPort()
{
    // Arrange
    Game::GameConfigurationProvider gameConfigurationProvider;
    Server::ServerMock server;
    Views::MainWindowModel model(server, gameConfigurationProvider);

    // Act
    model.GetPort() = 6666;
    model.StartServer();

    // Assert
    QVERIFY(6666 == server.GetPortServerStartedOn());
}

void MainWindowModelTests::ConfiguresGameUpdateTime()
{
    // Arrange
    Game::GameConfigurationProvider gameConfigurationProvider;
    Server::ServerMock server;
    Views::MainWindowModel model(server, gameConfigurationProvider);

    // Assert
    QVERIFY(0 == model.GetUpdateTime().GetValue());
}

void MainWindowModelTests::GameUpdateTimeIsZeroInitially()
{
    // Arrange
    Game::GameConfigurationProvider gameConfigurationProvider;
    Server::ServerMock server;
    Views::MainWindowModel model(server, gameConfigurationProvider);

    // Act
    model.GetUpdateTime() = 2000;
    model.ConfigureGame();


    // Assert
    QVERIFY(2000 == gameConfigurationProvider.GetGameUpdateTime());
}

void MainWindowModelTests::EmitsFailureSignalToStartServerWhenFailingToStartServer()
{
    // Arrange
    Game::GameConfigurationProvider gameConfigurationProvider;
    Server::ServerMock server;
    Views::MainWindowModel model(server, gameConfigurationProvider);
    server.SetServerStartResult(false);
    QSignalSpy spy(&model, SIGNAL(FailedToStartServer()));

    // Act
    model.StartServer();

    // Assert
    QVERIFY(1 == spy.count());
}

void MainWindowModelTests::EmitsSuccessSignalToStartServerWhenSucceedingToStartServer()
{
    // Arrange
    Game::GameConfigurationProvider gameConfigurationProvider;
    Server::ServerMock server;
    Views::MainWindowModel model(server, gameConfigurationProvider);
    QSignalSpy spy(&model, SIGNAL(SuccessToStartServer()));

    // Act
    model.StartServer();

    // Assert
    QVERIFY(1 == spy.count());
}

void MainWindowModelTests::CanCloseServer()
{
    // Arrange
    Game::GameConfigurationProvider gameConfigurationProvider;
    Server::ServerMock server;
    Views::MainWindowModel model(server, gameConfigurationProvider);

    // Act
    model.CloseServer();

    // Assert
    QVERIFY(server.GetServerClosed());
}
