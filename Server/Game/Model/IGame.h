#pragma once
#include <vector>
#include <functional>

#include "GameUnit.h"
#include "Point.h"

namespace Game
{
    namespace Model
    {
        class IGame
        {
        public:
            virtual ~IGame() {}

            virtual GameUnit GetUnit(const Point& point) const = 0;
            virtual void InsertUnit(const GameUnit& unit) = 0;
            virtual bool IsValid() const = 0;
            virtual std::vector<GameUnit> GetAll(const std::function<bool(const GameUnit&)>& predicate) const = 0;
            virtual bool GameIsLost() const = 0;
            virtual void LoseGame() = 0;
            virtual bool GameIsWon() const = 0;
            virtual void WinGame() = 0;
        };
    }
}
