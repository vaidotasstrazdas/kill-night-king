#pragma once
#include <string>
#include <vector>

#include "GameAction.h"

namespace Game
{
    namespace Protocol
    {
        /*
        Interface used to translate client's input to actual actions modifying the game.
        */
        class IGameProtocol
        {
        public:
            virtual ~IGameProtocol() {}

            virtual std::vector<GameAction> ResolveActions(const std::string& data) const = 0;
        };
    }
}
