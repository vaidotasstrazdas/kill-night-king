#include "Game/IGameConfigurationProvider.h"
#include "Server/IServer.h"

#include "MainWindowModel.h"

namespace Views
{
    MainWindowModel::MainWindowModel(Server::IServer& server, Game::IGameConfigurationProvider& gameConfigurationProvider)
        : m_server(server)
        , m_gameConfigurationProvider(gameConfigurationProvider)
        , m_columns(0)
        , m_rows(0)
        , m_zombiesToKill(0)
        , m_port(0)
        , m_updateTime(0)
    {
    }

    MainWindowModel::~MainWindowModel()
    {
    }

    void MainWindowModel::ConfigureGame()
    {
        m_gameConfigurationProvider.SetColumns(m_columns.GetValue());
        m_gameConfigurationProvider.SetRows(m_rows.GetValue());
        m_gameConfigurationProvider.SetZombiesToKill(m_zombiesToKill.GetValue());
        m_gameConfigurationProvider.SetGameUpdateTime(m_updateTime.GetValue());
    }

    void MainWindowModel::StartServer()
    {
        if (m_server.StartServer(m_port.GetValue()))
            emit SuccessToStartServer();
        else
            emit FailedToStartServer();
    }

    void MainWindowModel::CloseServer()
    {
        m_server.CloseServer();
    }

    ViewModelIntObject& MainWindowModel::GetColumns()
    {
        return m_columns;
    }

    ViewModelIntObject& MainWindowModel::GetRows()
    {
        return m_rows;
    }

    ViewModelIntObject& MainWindowModel::GetZombiesToKill()
    {
        return m_zombiesToKill;
    }

    ViewModelIntObject& MainWindowModel::GetPort()
    {
        return m_port;
    }

    ViewModelIntObject& MainWindowModel::GetUpdateTime()
    {
        return m_updateTime;
    }
}
