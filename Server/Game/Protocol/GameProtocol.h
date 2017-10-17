#pragma once
#include <memory>

#include "IGameProtocol.h"

namespace Game
{
    namespace Protocol
    {
        class GameProtocol
            : public IGameProtocol
        {
        public:
            GameProtocol();
            virtual ~GameProtocol();

            virtual std::vector<GameAction> ResolveActions(const std::string& data) const override;

        private:
            class Impl;
            std::unique_ptr<Impl> m_impl;
        };
    }
}
