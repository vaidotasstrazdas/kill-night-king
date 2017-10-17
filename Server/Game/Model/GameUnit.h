#pragma once
#include "GameUnitType.h"
#include "Point.h"

namespace Game
{
    namespace Model
    {
        struct GameUnit
        {
            GameUnit();
            GameUnit(const Point& point, GameUnitType type);

            Point m_point;
            GameUnitType m_type;

            bool IsValid() const;
        };
    }
}
