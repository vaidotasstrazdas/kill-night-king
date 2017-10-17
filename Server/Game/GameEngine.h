#pragma once
#include <memory>

#include "IGameEngine.h"

namespace Game
{
    class IGameConfigurationProvider;

    namespace Protocol
    {
        class IGameProtocol;
    }

    class GameEngine
        : public IGameEngine
    {
    public:
        GameEngine(const Protocol::IGameProtocol& protocol, const IGameConfigurationProvider& gameConfigurationProvider);
        virtual ~GameEngine();

        virtual std::string CreateGame() override;
        virtual Model::Game& GetGame(const std::string& gameId) override;
        virtual bool UpdateGame(const std::string& gameId, const std::string& data) override;
        virtual std::vector<std::string> GetChangeLog(const std::string& gameId) const override;
        virtual void UpdateGameAutomatically(const std::string& gameId) override;

    private:
        class Impl;
        std::unique_ptr<Impl> m_impl;
    };
}
