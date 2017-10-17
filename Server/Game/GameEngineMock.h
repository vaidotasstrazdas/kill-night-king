#pragma once
#include <memory>

#include "IGameEngine.h"

namespace Game
{
    class GameEngineMock
        : public IGameEngine
    {
    public:
        GameEngineMock();
        virtual ~GameEngineMock();

        virtual std::string CreateGame() override;
        virtual Model::Game& GetGame(const std::string& gameId) override;
        virtual bool UpdateGame(const std::string& gameId, const std::string& data) override;
        virtual std::vector<std::string> GetChangeLog(const std::string& gameId) const override;
        virtual void UpdateGameAutomatically(const std::string& gameId) override;

        void SetUpdateGameResult(bool result);
        bool GetGameUpdateExecuted() const;
        const std::string& GetLastGameIdUpdated() const;
        const std::string& GetLastDataUsedForGameUpdate() const;
        void SetChangeLog(const std::vector<std::string>& changeLog);
        const std::string& GetLastGameIdUpdatedAutomatically() const;

    private:
        std::unique_ptr<Model::Game> m_game;
        bool m_updateGameResult;
        bool m_gameUpdateExecuted;
        std::string m_lastGameIdUpdated;
        std::string m_lastDataUsedForGameUpdate;
        std::vector<std::string> m_changeLog;
        std::string m_lastGameIdUpdatedAutomatically;
    };
}
