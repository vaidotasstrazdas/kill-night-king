#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>

#include "Game/IClientGameChannel.h"
#include "Util/ClientSocketHolder.h"
#include "Util/ILogger.h"
#include "ClientSocketThread.h"
#include "Server.h"

namespace Server
{
    Server::Server(Game::IClientGameChannel& clientGameChannel, Util::ILogger& logger, const Game::IGameConfigurationProvider& gameConfigurationProvider)
        : m_clientGameChannel(clientGameChannel)
        , m_logger(logger)
        , m_gameConfigurationProvider(gameConfigurationProvider)
    {
    }

    Server::~Server()
    {
        CloseServer();
    }

    void Server::ConnectToClient()
    {
        m_logger.Log("Server", "Received new client.");
        QTcpSocket* socket = m_server->nextPendingConnection();
        if (!socket)
        {
            m_logger.Log("Server", "Somehow, no connection happened to go here. It was a false alarm. Waiting for new clients.");
            return;
        }

        std::unique_ptr<Util::IClientSocketHolder> clientSocket;
        clientSocket.reset(new Util::ClientSocketHolder(socket));

        m_clientGameChannel.CreateGameForClient(*clientSocket);
        m_clientGameChannel.ConfigureDataAppendFromClient(*clientSocket);

        std::unique_ptr<ClientSocketThread> socketThread;
        socketThread.reset(new ClientSocketThread(std::move(clientSocket), m_clientGameChannel, m_logger, m_gameConfigurationProvider));

        auto socketThreadPtr = socketThread.get();
        connect(socketThread.get(), &QThread::finished, this, [this, socketThreadPtr]
        {
            auto it = std::find_if(m_threads.begin(), m_threads.end(), [socketThreadPtr](const std::unique_ptr<ClientSocketThread>& item)
            {
                return item.get() == socketThreadPtr;
            });

            if (it != m_threads.end())
            {
                m_logger.Log("Server", "Client socket thread '" + socketThreadPtr->GetClientSocketIdentifier() + "' closed.");
                m_threads.erase(it);
            }
        });

        m_logger.Log("Server", "Client socket thread has been created. It is identified as '" + socketThread->GetClientSocketIdentifier() + "'.");
        socketThread->OnClose([this, socketThreadPtr]
        {
            m_logger.Log("Server", "Client socket thread '" + socketThreadPtr->GetClientSocketIdentifier() + "' is closing.");
            socketThreadPtr->quit();
        });
        socketThread->Initialize();
        m_logger.Log("Server", "Client socket thread '" + socketThread->GetClientSocketIdentifier() + "' has been initialized.");
        m_threads.push_back(std::move(socketThread));
    }

    bool Server::StartServer(unsigned int port)
    {
        m_server.reset(new QTcpServer(this));

        if(!m_server->listen(QHostAddress::Any, port))
        {
            m_logger.Log("Server", "Server was unable to start.");
            return false;
        }
        else
            m_logger.Log("Server", "Server started, and is listening to port " + std::to_string(port) + ".");

        connect(m_server.get(), &QTcpServer::newConnection, this, &Server::ConnectToClient);

        return true;
    }

    void Server::CloseServer()
    {
        for (auto& thread : m_threads)
        {
            thread->Close();
            thread->quit();
        }
    }
}
