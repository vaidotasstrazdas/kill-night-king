#pragma once
#include "TestCollector.h"
#include "Game/GameEngineMock.h"
#include "Game/ClientGameChannel.h"
#include "Util/ClientSocketHolderMock.h"

class ClientGameChannelTests
    : public QObject
{
    Q_OBJECT

public:
    ClientGameChannelTests();
    virtual ~ClientGameChannelTests();

private slots:
    void WritesCorrectBytesWhenStartingGame();
    void ExecutesGameUpdate();
    void ExecutesGameUpdateOnCorrectGameId();
    void ExecutesGameUpdateOnCorrectGameData();
    void DoesNotLoseAnyData();
    void MergesDataUntilAbleToCompletelyUpdateGameState();
    void ChangeLogIsWrittenToClient();
    void GameIsUpdatedAutomaticallyOnClientNotification();
    void ChangeLogIsWrittenToClientOnClientNotification();
    void SocketIsClosedWhenGameIsLost();
    void SocketIsClosedWhenGameIsWon();
};
ADD_TEST(ClientGameChannelTests)
