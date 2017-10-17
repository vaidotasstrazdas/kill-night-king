#pragma once
#include "TestCollector.h"
#include "Game/GameConfigurationProvider.h"
#include "Server/ServerMock.h"
#include "Views/MainWindowModel.h"

class MainWindowModelTests
    : public QObject
{
    Q_OBJECT

    public:
        MainWindowModelTests();
        virtual ~MainWindowModelTests();

    private slots:
        void SetsInitialValues();
        void ConfiguresGame();
        void StartsServerToListenToSpecifiedPort();
        void ConfiguresGameUpdateTime();
        void GameUpdateTimeIsZeroInitially();
        void EmitsFailureSignalToStartServerWhenFailingToStartServer();
        void EmitsSuccessSignalToStartServerWhenSucceedingToStartServer();
        void CanCloseServer();

};
ADD_TEST(MainWindowModelTests)
