#pragma once
#include "../Model/Point.h"
#include "GameActionType.h"

namespace Game
{
    namespace Protocol
    {
        struct GameAction
        {
            GameAction();
            GameAction(GameActionType type, const Model::Point& activator, const Model::Point& affected);

            GameActionType m_type;
            Model::Point m_activator;
            Model::Point m_affected;
        };
    }
}
