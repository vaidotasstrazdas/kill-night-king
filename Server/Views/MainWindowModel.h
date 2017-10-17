#pragma once
#include "DataBinding/ViewModelObject.h"
#include "DataBinding/ViewModelBase.h"

namespace Game
{
    class IGameConfigurationProvider;
}

namespace Server
{
    class IServer;
}

namespace Views
{
    class MainWindowModel
        : public ViewModelBase
    {
        Q_OBJECT
    public:
        MainWindowModel(Server::IServer& server, Game::IGameConfigurationProvider& gameConfigurationProvider);
        virtual ~MainWindowModel();

        void ConfigureGame();
        void StartServer();
        void CloseServer();

        ViewModelIntObject& GetColumns();
        ViewModelIntObject& GetRows();
        ViewModelIntObject& GetZombiesToKill();
        ViewModelIntObject& GetPort();
        ViewModelIntObject& GetUpdateTime();

    signals:
        void FailedToStartServer();
        void SuccessToStartServer();

    private:
        Server::IServer& m_server;
        Game::IGameConfigurationProvider& m_gameConfigurationProvider;
        ViewModelIntObject m_columns;
        ViewModelIntObject m_rows;
        ViewModelIntObject m_zombiesToKill;
        ViewModelIntObject m_port;
        ViewModelIntObject m_updateTime;
    };
}
