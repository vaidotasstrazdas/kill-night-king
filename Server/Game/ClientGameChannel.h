#pragma once
#include <memory>

#include "IClientGameChannel.h"

namespace Game
{
    class IGameEngine;

    class ClientGameChannel
        : public IClientGameChannel
    {
    public:
        ClientGameChannel(IGameEngine& gameEngine);
        virtual ~ClientGameChannel();

        virtual void CreateGameForClient(Util::IClientSocketHolder& socket) override;
        virtual void ConfigureDataAppendFromClient(Util::IClientSocketHolder& socket) override;
        virtual void NotifyClient(Util::IClientSocketHolder& socket) override;

    private:
        class Impl;
        std::unique_ptr<Impl> m_impl;
    };
}
