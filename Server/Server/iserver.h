#pragma once

namespace Server
{
    class IServer
    {
    public:
        virtual ~IServer() {}

        virtual bool StartServer(unsigned int port) = 0;

        virtual void CloseServer() = 0;
    };
}
