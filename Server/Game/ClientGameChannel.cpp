#pragma once
#include <map>
#include <memory>

#include <QMutex>
#include <qdebug.h>

#include "ClientGameChannel.h"
#include "IGameEngine.h"

namespace Game
{
    class ClientGameChannel::Impl
    {
    public:
        Impl(IGameEngine& gameEngine)
            : m_gameEngine(gameEngine)
        {
        }

        ~Impl()
        {
        }

        void CreateGameForClient(Util::IClientSocketHolder& socket)
        {
            // std::map is not thread-safe for modification, thus lock is used here.
            m_mutex.lock();

            const auto gameId = m_gameEngine.CreateGame();
            m_games[&socket] = gameId;
            m_data[&socket] = "";

            m_mutex.unlock();

            // Notify client that game has started.
            socket.WriteBytes("Hello. I am corrupt Westeros and desperate for your help to defend me from hordes of zombies.\nI beg your help!!!\n\n");
        }

        void ConfigureDataAppendFromClient(Util::IClientSocketHolder& socket)
        {
            socket.WhenBytesReady([this, &socket](const QByteArray& bytes)
            {
                // std::map is not thread-safe for modification, thus lock is used here.
                m_mutex.lock();

                m_data[&socket] += bytes.toStdString();
                const auto gameId = m_games.at(&socket);
                qDebug() << &socket << ": " << m_data.at(&socket).c_str();
                if (m_gameEngine.UpdateGame(gameId, m_data.at(&socket)))
                {
                    m_data[&socket] = ""; // No need to keep the buffer if we were able to use client's data.

                    NotifyChangeLog(socket);
                    CloseIfWonOrLost(socket);
                }

                m_mutex.unlock();
            });
        }

        void NotifyClient(Util::IClientSocketHolder& socket)
        {
            // std::map is not thread-safe for modification, thus lock is used here.
            m_mutex.lock();

            const auto gameId = m_games.at(&socket);
            m_gameEngine.UpdateGameAutomatically(gameId);
            NotifyChangeLog(socket);
            CloseIfWonOrLost(socket);

            m_mutex.unlock();
        }

    private:
        void NotifyChangeLog(Util::IClientSocketHolder& socket)
        {
            const auto gameId = m_games.at(&socket);

            // Prepare change log to write.
            std::string logEventToWrite = "";
            for (const auto& logEvent : m_gameEngine.GetChangeLog(gameId))
                logEventToWrite += logEvent + "\n";

            // Write bytes to client socket.
            QByteArray logEventBytes(logEventToWrite.c_str(), logEventToWrite.length());
            socket.WriteBytes(logEventBytes);
        }

        void CloseIfWonOrLost(Util::IClientSocketHolder& socket)
        {
            const auto gameId = m_games.at(&socket);
            auto& game = m_gameEngine.GetGame(gameId);
            if (game.GameIsWon() || game.GameIsLost())
                socket.Close();
        }

    private:
        IGameEngine& m_gameEngine;
        std::map<Util::IClientSocketHolder*, std::string> m_games;
        std::map<Util::IClientSocketHolder*, std::string> m_data;
        QMutex m_mutex;
    };

    ClientGameChannel::ClientGameChannel(IGameEngine& gameEngine)
        : m_impl(new Impl(gameEngine))
    {
    }

    ClientGameChannel::~ClientGameChannel()
    {
    }

    void ClientGameChannel::CreateGameForClient(Util::IClientSocketHolder& socket)
    {
        m_impl->CreateGameForClient(socket);
    }

    void ClientGameChannel::ConfigureDataAppendFromClient(Util::IClientSocketHolder& socket)
    {
        m_impl->ConfigureDataAppendFromClient(socket);
    }

    void ClientGameChannel::NotifyClient(Util::IClientSocketHolder& socket)
    {
        m_impl->NotifyClient(socket);
    }
}
