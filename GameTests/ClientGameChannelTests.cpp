#include "ClientGameChannelTests.h"

ClientGameChannelTests::ClientGameChannelTests()
{
}

ClientGameChannelTests::~ClientGameChannelTests()
{
}

void ClientGameChannelTests::WritesCorrectBytesWhenStartingGame()
{
    // Arrange
    Util::ClientSocketHolderMock clientSocketHolder;
    Game::GameEngineMock gameEngine;
    Game::ClientGameChannel channel(gameEngine);

    // Act
    channel.CreateGameForClient(clientSocketHolder);

    // Assert
    QVERIFY("Hello. I am corrupt Westeros and desperate for your help to defend me from hordes of zombies.\nI beg your help!!!\n\n" == clientSocketHolder.GetLastBytesWritten());
}

void ClientGameChannelTests::ExecutesGameUpdate()
{
    // Arrange
    Util::ClientSocketHolderMock clientSocketHolder;
    Game::GameEngineMock gameEngine;
    Game::ClientGameChannel channel(gameEngine);

    // Act
    channel.CreateGameForClient(clientSocketHolder);
    channel.ConfigureDataAppendFromClient(clientSocketHolder);
    clientSocketHolder.SetBytesReady("game-data");

    // Assert
    QVERIFY(gameEngine.GetGameUpdateExecuted());
}

void ClientGameChannelTests::ExecutesGameUpdateOnCorrectGameId()
{
    // Arrange
    Util::ClientSocketHolderMock clientSocketHolder;
    Game::GameEngineMock gameEngine;
    Game::ClientGameChannel channel(gameEngine);

    // Act
    channel.CreateGameForClient(clientSocketHolder);
    channel.ConfigureDataAppendFromClient(clientSocketHolder);
    clientSocketHolder.SetBytesReady("game-data");

    // Assert
    QVERIFY("game" == gameEngine.GetLastGameIdUpdated());
}

void ClientGameChannelTests::ExecutesGameUpdateOnCorrectGameData()
{
    // Arrange
    Util::ClientSocketHolderMock clientSocketHolder;
    Game::GameEngineMock gameEngine;
    Game::ClientGameChannel channel(gameEngine);

    // Act
    channel.CreateGameForClient(clientSocketHolder);
    channel.ConfigureDataAppendFromClient(clientSocketHolder);
    clientSocketHolder.SetBytesReady("game-data");

    // Assert
    QVERIFY("game-data" == gameEngine.GetLastDataUsedForGameUpdate());
}

void ClientGameChannelTests::DoesNotLoseAnyData()
{
    // Arrange
    Util::ClientSocketHolderMock clientSocketHolder;
    Game::GameEngineMock gameEngine;
    Game::ClientGameChannel channel(gameEngine);

    // Act & Assert
    channel.CreateGameForClient(clientSocketHolder);
    channel.ConfigureDataAppendFromClient(clientSocketHolder);

    clientSocketHolder.SetBytesReady("game-data");
    QVERIFY("game-data" == gameEngine.GetLastDataUsedForGameUpdate());

    clientSocketHolder.SetBytesReady("abcdefgh");
    QVERIFY("abcdefgh" == gameEngine.GetLastDataUsedForGameUpdate());

    clientSocketHolder.SetBytesReady("123456");
    QVERIFY("123456" == gameEngine.GetLastDataUsedForGameUpdate());
}

void ClientGameChannelTests::MergesDataUntilAbleToCompletelyUpdateGameState()
{
    // Arrange
    Util::ClientSocketHolderMock clientSocketHolder;
    Game::GameEngineMock gameEngine;
    Game::ClientGameChannel channel(gameEngine);

    // Act & Assert
    channel.CreateGameForClient(clientSocketHolder);
    channel.ConfigureDataAppendFromClient(clientSocketHolder);

    gameEngine.SetUpdateGameResult(false);

    clientSocketHolder.SetBytesReady("a");
    QVERIFY("a" == gameEngine.GetLastDataUsedForGameUpdate());

    clientSocketHolder.SetBytesReady("b");
    QVERIFY("ab" == gameEngine.GetLastDataUsedForGameUpdate());

    clientSocketHolder.SetBytesReady("c");
    QVERIFY("abc" == gameEngine.GetLastDataUsedForGameUpdate());

    gameEngine.SetUpdateGameResult(true);

    clientSocketHolder.SetBytesReady("d");
    QVERIFY("abcd" == gameEngine.GetLastDataUsedForGameUpdate());

    clientSocketHolder.SetBytesReady("no-merge");
    QVERIFY("no-merge" == gameEngine.GetLastDataUsedForGameUpdate());
}

void ClientGameChannelTests::ChangeLogIsWrittenToClient()
{
    // Arrange
    Util::ClientSocketHolderMock clientSocketHolder;
    Game::GameEngineMock gameEngine;
    Game::ClientGameChannel channel(gameEngine);
    gameEngine.SetChangeLog({
        "Game Event One",
        "Game Event Two",
    });

    // Act
    channel.CreateGameForClient(clientSocketHolder);
    channel.ConfigureDataAppendFromClient(clientSocketHolder);
    clientSocketHolder.SetBytesReady("game-data");

    // Assert
    QVERIFY("Game Event One\nGame Event Two\n" == clientSocketHolder.GetLastBytesWritten());
}

void ClientGameChannelTests::GameIsUpdatedAutomaticallyOnClientNotification()
{
    // Arrange
    Util::ClientSocketHolderMock clientSocketHolder;
    Game::GameEngineMock gameEngine;
    Game::ClientGameChannel channel(gameEngine);

    // Act
    channel.CreateGameForClient(clientSocketHolder);
    channel.NotifyClient(clientSocketHolder);

    // Assert
    QVERIFY("game" == gameEngine.GetLastGameIdUpdatedAutomatically());
}

void ClientGameChannelTests::ChangeLogIsWrittenToClientOnClientNotification()
{
    // Arrange
    Util::ClientSocketHolderMock clientSocketHolder;
    Game::GameEngineMock gameEngine;
    Game::ClientGameChannel channel(gameEngine);
    gameEngine.SetChangeLog({
        "Game Event One",
        "Game Event Two",
    });

    // Act
    channel.CreateGameForClient(clientSocketHolder);
    channel.NotifyClient(clientSocketHolder);

    // Assert
    QVERIFY("Game Event One\nGame Event Two\n" == clientSocketHolder.GetLastBytesWritten());
}

void ClientGameChannelTests::SocketIsClosedWhenGameIsLost()
{
    // Arrange
    Util::ClientSocketHolderMock clientSocketHolder;
    Game::GameEngineMock gameEngine;
    Game::ClientGameChannel channel(gameEngine);

    // Act
    channel.CreateGameForClient(clientSocketHolder);
    gameEngine.GetGame("").LoseGame();
    bool closed = false;
    clientSocketHolder.OnClose([&closed]
    {
        closed = true;
    });
    channel.NotifyClient(clientSocketHolder);

    // Assert
    QVERIFY(closed);
}

void ClientGameChannelTests::SocketIsClosedWhenGameIsWon()
{
    // Arrange
    Util::ClientSocketHolderMock clientSocketHolder;
    Game::GameEngineMock gameEngine;
    Game::ClientGameChannel channel(gameEngine);
    gameEngine.SetChangeLog({
        "Game Event One",
        "Game Event Two",
    });

    // Act
    channel.CreateGameForClient(clientSocketHolder);
    gameEngine.GetGame("").LoseGame();
    bool closed = false;
    clientSocketHolder.OnClose([&closed]
    {
        closed = true;
    });
    channel.ConfigureDataAppendFromClient(clientSocketHolder);
    clientSocketHolder.SetBytesReady("game-data");

    // Assert
    QVERIFY(closed);
}
