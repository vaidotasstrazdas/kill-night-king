#pragma once
#include "IServer.h"

namespace Server
{
    class ServerMock
        : public IServer
    {
    public:
        ServerMock();
        virtual ~ServerMock();

        virtual bool StartServer(unsigned int port) override;
        virtual void CloseServer() override;

        unsigned int GetPortServerStartedOn() const;
        void SetServerStartResult(bool serverStartResult);
        bool GetServerClosed() const;

    private:
        unsigned int m_portStartedOn;
        bool m_serverStartResult;
        bool m_serverClosed;
    };
}
