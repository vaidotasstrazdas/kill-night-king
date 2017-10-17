#pragma once
#include <memory>

#include "IGame.h"

namespace Game
{
    namespace Model
    {
        class Game
            : public IGame
        {
        public:
            Game();
            virtual ~Game();

            virtual GameUnit GetUnit(const Point& point) const override;
            virtual void InsertUnit(const GameUnit& unit) override;
            virtual bool IsValid() const override;
            virtual std::vector<GameUnit> GetAll(const std::function<bool(const GameUnit&)>& predicate) const override;
            virtual bool GameIsLost() const override;
            virtual void LoseGame() override;
            virtual bool GameIsWon() const override;
            virtual void WinGame() override;

        private:
            class Impl;
            std::unique_ptr<Impl> m_impl;
        };
    }
}
