#pragma once
#include <string>

#include "Model/Game.h"

namespace Game
{
    class IGameEngine
    {
    public:
        virtual ~IGameEngine() {}

        // Creates game, and returns specified ID.
        virtual std::string CreateGame() = 0;

        // Returns Model::Game instance by specified game id.
        // Returned object is invalid if game by specified id does not exist.
        virtual Model::Game& GetGame(const std::string& gameId) = 0;

        // Client sends some queries, and game engine, using that data, updates the game based on data if possible.
        // In other words, true is returned if game state changes.
        virtual bool UpdateGame(const std::string& gameId, const std::string& data) = 0;

        // Get what happened.
        virtual std::vector<std::string> GetChangeLog(const std::string& gameId) const = 0;

        // Update game state from the server side.
        virtual void UpdateGameAutomatically(const std::string& gameId) = 0;
    };
}
