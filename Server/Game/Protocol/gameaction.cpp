#include "GameAction.h"

namespace Game
{
    namespace Protocol
    {
        GameAction::GameAction()
            : GameAction(GameActionType::Unknown, Model::Point::Point(), Model::Point::Point())
        {
        }

        GameAction::GameAction(GameActionType type, const Model::Point& activator, const Model::Point& affected)
            : m_type(type)
            , m_activator(activator)
            , m_affected(affected)
        {
        }
    }
}
