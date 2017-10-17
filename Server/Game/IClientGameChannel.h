#pragma once
#include "Util/IClientSocketHolder.h"

namespace Game
{
    class IClientGameChannel
    {
    public:
        virtual ~IClientGameChannel() {}

        virtual void CreateGameForClient(Util::IClientSocketHolder& socket) = 0;
        virtual void ConfigureDataAppendFromClient(Util::IClientSocketHolder& socket) = 0;
        virtual void NotifyClient(Util::IClientSocketHolder& socket) = 0;
    };
}
