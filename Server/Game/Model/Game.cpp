#include <map>

#include "Game.h"

namespace Game
{
    namespace Model
    {
        class Game::Impl
        {
        public:
            Impl()
                : m_gameLost(false)
                , m_gameWon(false)
            {
            }

            ~Impl()
            {
            }

            bool IsValid() const
            {
                return !m_units.empty();
            }

            GameUnit GetUnit(const Point& point) const
            {
                if (m_units.find(point) != m_units.end())
                    return m_units.at(point);

                return GameUnit();
            }

            void InsertUnit(const GameUnit& unit)
            {
                // Unit will be either updated or created.
                m_units[unit.m_point] = unit;
            }

            std::vector<GameUnit> GetAll(const std::function<bool(const GameUnit&)>& predicate)
            {
                std::vector<GameUnit> units;
                for (const auto& kvp : m_units)
                {
                    const auto& unit = kvp.second;
                    if (predicate(unit))
                        units.push_back(unit);
                }

                return units;
            }

            bool GameIsLost() const
            {
                return m_gameLost;
            }

            void LoseGame()
            {
                m_gameLost = true;
            }

            bool GameIsWon() const
            {
                return m_gameLost;
            }

            void WinGame()
            {
                m_gameLost = true;
            }

        private:
            std::map<Point, GameUnit> m_units;
            bool m_gameLost;
            bool m_gameWon;
        };

        Game::Game()
            : m_impl(new Impl())
        {
        }

        Game::~Game()
        {
        }

        GameUnit Game::GetUnit(const Point& point) const
        {
            return m_impl->GetUnit(point);
        }

        void Game::InsertUnit(const GameUnit& unit)
        {
            return m_impl->InsertUnit(unit);
        }

        bool Game::IsValid() const
        {
            return m_impl->IsValid();
        }

        std::vector<GameUnit> Game::GetAll(const std::function<bool(const GameUnit&)>& predicate) const
        {
            return m_impl->GetAll(predicate);
        }

        bool Game::GameIsLost() const
        {
            return m_impl->GameIsLost();
        }

        void Game::LoseGame()
        {
            m_impl->LoseGame();
        }

        bool Game::GameIsWon() const
        {
            return m_impl->GameIsWon();
        }

        void Game::WinGame()
        {
            m_impl->WinGame();
        }
    }
}
