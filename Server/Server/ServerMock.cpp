#include "ServerMock.h"

namespace Server
{
    ServerMock::ServerMock()
        : m_portStartedOn(0)
        , m_serverStartResult(true)
        , m_serverClosed(false)
    {
    }

    ServerMock::~ServerMock()
    {
    }

    bool ServerMock::StartServer(unsigned int port)
    {
        m_portStartedOn = port;
        return m_serverStartResult;
    }

    void ServerMock::CloseServer()
    {
        m_serverClosed = true;
    }

    unsigned int ServerMock::GetPortServerStartedOn() const
    {
        return m_portStartedOn;
    }

    void ServerMock::SetServerStartResult(bool serverStartResult)
    {
        m_serverStartResult = serverStartResult;
    }

    bool ServerMock::GetServerClosed() const
    {
        return m_serverClosed;
    }
}
