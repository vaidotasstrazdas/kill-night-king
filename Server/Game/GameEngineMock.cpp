#include "GameEngineMock.h"

namespace Game
{
    GameEngineMock::GameEngineMock()
        : m_game(new Model::Game())
        , m_updateGameResult(true)
        , m_gameUpdateExecuted(false)
        , m_lastGameIdUpdated("")
        , m_lastDataUsedForGameUpdate("")
        , m_lastGameIdUpdatedAutomatically("")
    {
    }

    GameEngineMock::~GameEngineMock()
    {
    }

    std::string GameEngineMock::CreateGame()
    {
        return "game";
    }

    Model::Game& GameEngineMock::GetGame(const std::string&)
    {
        return *m_game;
    }

    bool GameEngineMock::UpdateGame(const std::string& gameId, const std::string& data)
    {
        m_lastGameIdUpdated = gameId;
        m_lastDataUsedForGameUpdate = data;
        m_gameUpdateExecuted = true;

        return m_updateGameResult;
    }

    std::vector<std::string> GameEngineMock::GetChangeLog(const std::string&) const
    {
        return m_changeLog;
    }

    void GameEngineMock::UpdateGameAutomatically(const std::string& gameId)
    {
        m_lastGameIdUpdatedAutomatically = gameId;
    }

    void GameEngineMock::SetUpdateGameResult(bool result)
    {
        m_updateGameResult = result;
    }

    bool GameEngineMock::GetGameUpdateExecuted() const
    {
        return m_gameUpdateExecuted;
    }

    const std::string& GameEngineMock::GetLastGameIdUpdated() const
    {
        return m_lastGameIdUpdated;
    }

    const std::string& GameEngineMock::GetLastDataUsedForGameUpdate() const
    {
        return m_lastDataUsedForGameUpdate;
    }

    void GameEngineMock::SetChangeLog(const std::vector<std::string>& changeLog)
    {
        m_changeLog = changeLog;
    }

    const std::string& GameEngineMock::GetLastGameIdUpdatedAutomatically() const
    {
        return m_lastGameIdUpdatedAutomatically;
    }
}
