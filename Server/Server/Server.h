#pragma once
#include <memory>
#include <vector>

#include <QObject>

#include "IServer.h"

class QTcpServer;
class QTcpSocket;
class QTimer;

namespace Game
{
    class IClientGameChannel;
    class IGameConfigurationProvider;
}

namespace Util
{
    class IClientSocketHolder;
    class ILogger;
}

class ClientSocketThread;

namespace Server
{
    class Server
        : public QObject
        , public IServer
    {
    public:
        Server(Game::IClientGameChannel& clientGameChannel, Util::ILogger& logger, const Game::IGameConfigurationProvider& gameConfigurationProvider);
        virtual ~Server();

        virtual bool StartServer(unsigned int port) override;
        virtual void CloseServer() override;

    private slots:
        void ConnectToClient();

    private:
        Game::IClientGameChannel& m_clientGameChannel;
        Util::ILogger& m_logger;
        const Game::IGameConfigurationProvider& m_gameConfigurationProvider;
        std::unique_ptr<QTcpServer> m_server;
        std::vector<std::unique_ptr<ClientSocketThread>> m_threads;
    };
}
