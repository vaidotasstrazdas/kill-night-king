#include "GameUnit.h"

namespace Game
{
    namespace Model
    {
        GameUnit::GameUnit()
            : GameUnit(Point(), GameUnitType::Unknwon)
        {
        }

        GameUnit::GameUnit(const Point& point, GameUnitType type)
            : m_point(point)
            , m_type(type)
        {
        }

        bool GameUnit::IsValid() const
        {
            return m_type != GameUnitType::Unknwon;
        }
    }
}
