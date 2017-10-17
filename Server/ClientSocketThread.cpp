#include <QTimer>

#include "Game/IClientGameChannel.h"
#include "Game/IGameConfigurationProvider.h"
#include "Util/IClientSocketHolder.h"
#include "Util/ILogger.h"
#include "Util/Random.h"

#include "ClientSocketThread.h"

ClientSocketThread::ClientSocketThread(std::unique_ptr<Util::IClientSocketHolder> socket, Game::IClientGameChannel& clientGameChannel, Util::ILogger& logger,
                                       const Game::IGameConfigurationProvider& gameConfigurationProvider)
    : m_socket(std::move(socket))
    , m_clientGameChannel(clientGameChannel)
    , m_logger(logger)
    , m_gameConfigurationProvider(gameConfigurationProvider)
    , m_clientSocketIdentifier("Socket " + Util::Random::GenerateRandomString())
{
}

ClientSocketThread::~ClientSocketThread()
{
}

void ClientSocketThread::Initialize()
{
    m_logger.Log(m_clientSocketIdentifier, "Initializing the client thread.");
    m_statusUpdateTimer.reset(new QTimer());
    m_statusUpdateTimer->setInterval(m_gameConfigurationProvider.GetGameUpdateTime());

    connect(m_statusUpdateTimer.get(), &QTimer::timeout, this, [this]
    {
        m_logger.Log(m_clientSocketIdentifier, "Notifying the client.");
        m_clientGameChannel.NotifyClient(*m_socket);
    });

    m_socket->OnClose([this]
    {
        m_logger.Log(m_clientSocketIdentifier, "Closing the thread.");
        m_statusUpdateTimer->stop();

        if (m_onClose)
            m_onClose();
    });

    m_statusUpdateTimer->start();
    this->start();
}

void ClientSocketThread::OnClose(const std::function<void()>& onClose)
{
    m_onClose = onClose;
}

std::string ClientSocketThread::GetClientSocketIdentifier() const
{
    return m_clientSocketIdentifier;
}

void ClientSocketThread::Close()
{
    m_socket->Close();
}
