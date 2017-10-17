#pragma once
#include <functional>
#include <memory>

#include <QThread>

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

class QTimer;

class ClientSocketThread
    : public QThread
{
    Q_OBJECT
public:
    ClientSocketThread(std::unique_ptr<Util::IClientSocketHolder> socket, Game::IClientGameChannel& clientGameChannel, Util::ILogger& logger,
                       const Game::IGameConfigurationProvider& gameConfigurationProvider);
    virtual ~ClientSocketThread();

    void Initialize();
    void OnClose(const std::function<void()>& onClose);
    std::string GetClientSocketIdentifier() const;
    void Close();

private:
    std::unique_ptr<Util::IClientSocketHolder> m_socket;
    Game::IClientGameChannel& m_clientGameChannel;
    Util::ILogger& m_logger;
    const Game::IGameConfigurationProvider& m_gameConfigurationProvider;
    std::function<void()> m_onClose;
    std::unique_ptr<QTimer> m_statusUpdateTimer;
    std::string m_clientSocketIdentifier;
};
