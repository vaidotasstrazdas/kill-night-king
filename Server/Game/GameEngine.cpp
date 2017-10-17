#include <map>

#include "Util/Random.h"

#include "IGameConfigurationProvider.h"
#include "Protocol/IGameProtocol.h"
#include "GameEngine.h"
#include "Model/Point.h"

#include <QDebug>

namespace Game
{
    class GameEngine::Impl
    {
    public:
        Impl(const Protocol::IGameProtocol& protocol, const IGameConfigurationProvider& gameConfigurationProvider)
            : m_protocol(protocol)
            , m_gameConfigurationProvider(gameConfigurationProvider)
        {
            m_games[""].reset(new Model::Game());
        }

        ~Impl()
        {
        }

        std::string CreateGame()
        {
            std::string gameId = "";
            do
            {
                gameId = Util::Random::GenerateRandomString();
            } while (m_games.find(gameId) != m_games.end());

            m_games[gameId].reset(new Model::Game());
            m_zombiesKilled[gameId] = 0;
            m_changeLog[gameId] = {};

            InitializeGameInternal(gameId);
            PrepareGame(*m_games[gameId]);

            return gameId;
        }

        Model::Game& GetGame(const std::string& gameId)
        {
            if (m_games.find(gameId) != m_games.end())
                return *m_games[gameId];

            return *m_games[""];
        }

        bool UpdateGame(const std::string& gameId, const std::string& data)
        {
            auto& game = GetGame(gameId);

            // Updating invalid game is pointless.
            if (!game.IsValid())
                return false;

            m_changeLog[gameId].clear();
            const auto actions = m_protocol.ResolveActions(data);
            if (actions.empty())
                return false;

            for (const auto& action : actions)
                ExecuteAction(game, action, gameId);

            return true;
        }

        std::vector<std::string> GetChangeLog(const std::string& gameId)
        {
            if (m_changeLog.find(gameId) == m_changeLog.end())
                return {};

            return m_changeLog.at(gameId);
        }

        void UpdateGameAutomatically(const std::string& gameId)
        {
            auto& game = GetGame(gameId);
            if (!game.IsValid())
                return;

            m_changeLog[gameId].clear();

            // Move all zombies upwards.
            auto gameUnits = game.GetAll([](const Model::GameUnit& unit)
            {
                return unit.m_type == Model::GameUnitType::Zombie;
            });

            for (auto gameUnit : gameUnits)
                Move(game, gameUnit.m_point, Model::Point(gameUnit.m_point.m_x, gameUnit.m_point.m_y - 1), gameId);

            // Insert new zombie at the first empty cell at bottom.
            auto emptyGameUnits = game.GetAll([this](const Model::GameUnit& unit)
            {
                return unit.m_type == Model::GameUnitType::Empty && unit.m_point.m_y == m_gameConfigurationProvider.GetRows() - 1;
            });

            if (!emptyGameUnits.empty())
            {
                const auto& newZombiePoint = emptyGameUnits[0].m_point;
                game.InsertUnit(Model::GameUnit(newZombiePoint, Model::GameUnitType::Zombie));
                m_changeLog[gameId].push_back("Zombie has appeared at " + newZombiePoint.ToString() + ".");
            }
        }

    private:
        void InitializeGameInternal(const std::string& gameId)
        {
            auto& game = m_games[gameId];

            for (unsigned int x = 0; x < m_gameConfigurationProvider.GetColumns(); x++)
            {
                for (unsigned int y = 0; y < m_gameConfigurationProvider.GetRows(); y++)
                    game->InsertUnit(Model::GameUnit(Model::Point(x, y), Model::GameUnitType::Empty));
            }
        }

        void PrepareGame(Model::Game& game)
        {
            for (unsigned int x = 0; x < m_gameConfigurationProvider.GetColumns(); x++)
                game.InsertUnit(Model::GameUnit(Model::Point(x, 0), Model::GameUnitType::Wall));
        }

        void ExecuteAction(Model::Game& game, const Protocol::GameAction& action, const std::string& gameId)
        {
            switch (action.m_type)
            {
            case Protocol::GameActionType::Move:
                Move(game, action.m_activator, action.m_affected, gameId);
                break;
            case Protocol::GameActionType::Attack:
                Attack(game, action.m_activator, action.m_affected, gameId);
                break;
            default:
                return;
            }
        }

        void Move(Model::Game& game, const Model::Point& from, const Model::Point& to, const std::string& gameId)
        {
            auto fromUnit = game.GetUnit(from);
            auto toUnit = game.GetUnit(to);
            const auto isWall = toUnit.m_type == Model::GameUnitType::Wall;

            // Currently, only zombies will move. In the future, we can allow movement of client's warriors.
            if (fromUnit.m_type != Model::GameUnitType::Zombie)
                return;

            if (!isWall && toUnit.m_type != Model::GameUnitType::Empty)
                return; // Invalid movement direction.

            toUnit.m_type = fromUnit.m_type;
            fromUnit.m_type = Model::GameUnitType::Empty;
            game.InsertUnit(toUnit);
            game.InsertUnit(fromUnit);

            if (isWall)
            {
                m_changeLog[gameId].push_back("Zombie has reached the wall!!! Westeros is DOOMED!!! You have LOST!!!");
                game.LoseGame();
            }
            else
                m_changeLog[gameId].push_back("Zombie moved from " + fromUnit.m_point.ToString() + " to " + toUnit.m_point.ToString());
        }

        void Attack(Model::Game& game, const Model::Point& from, const Model::Point& to, const std::string& gameId)
        {
            // Currently, parameter 'from' can be ignored.
            // In the future, parameters, such as defence, attack accuracy can be introduced. Based on these parameters, having position from which attack happens would make sense.

            auto toUnit = game.GetUnit(to);
            if (toUnit.m_type == Model::GameUnitType::Zombie)
            {
                toUnit.m_type = Model::GameUnitType::Empty;
                m_changeLog[gameId].push_back("Your glorious archers killed the zombie at " + toUnit.m_point.ToString() + "! Congratz, pal!");
                game.InsertUnit(toUnit);
                m_zombiesKilled[gameId]++;
            }
            else
                m_changeLog[gameId].push_back("There are no zombies at " + toUnit.m_point.ToString() + "! Look where shooting!!! Don't you see Westeros is in danger?!!");

            if (m_zombiesKilled.at(gameId) == m_gameConfigurationProvider.GetZombiesToKill())
            {
                game.WinGame();
                m_changeLog[gameId].push_back("Night King pissed poorly and ran away from your glorious troops! Westeros is saved! At least for now...");
            }
        }

    private:
        const Protocol::IGameProtocol& m_protocol;
        const IGameConfigurationProvider& m_gameConfigurationProvider;
        std::map<std::string, std::unique_ptr<Model::Game>> m_games;
        std::map<std::string, std::vector<std::string>> m_changeLog;
        std::map<std::string, unsigned int> m_zombiesKilled;
    };

    GameEngine::GameEngine(const Protocol::IGameProtocol& protocol, const IGameConfigurationProvider& gameConfigurationProvider)
        : m_impl(new Impl(protocol, gameConfigurationProvider))
    {
    }

    GameEngine::~GameEngine()
    {
    }

    std::string GameEngine::CreateGame()
    {
        return m_impl->CreateGame();
    }

    Model::Game& GameEngine::GetGame(const std::string& gameId)
    {
        return m_impl->GetGame(gameId);
    }

    bool GameEngine::UpdateGame(const std::string& gameId, const std::string& data)
    {
        return m_impl->UpdateGame(gameId, data);
    }

    std::vector<std::string> GameEngine::GetChangeLog(const std::string& gameId) const
    {
        return m_impl->GetChangeLog(gameId);
    }

    void GameEngine::UpdateGameAutomatically(const std::string& gameId)
    {
        m_impl->UpdateGameAutomatically(gameId);
    }
}
