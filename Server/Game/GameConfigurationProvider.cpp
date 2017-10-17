#include "GameConfigurationProvider.h"

namespace Game
{
    struct GameConfigurationProvider::Impl
    {
        Impl()
            : m_columns(0)
            , m_rows(0)
            , m_zombiesToKill(0)
            , m_updateTime(0)
        {
        }

        unsigned int m_columns;
        unsigned int m_rows;
        unsigned int m_zombiesToKill;
        unsigned int m_updateTime;
    };

    GameConfigurationProvider::GameConfigurationProvider()
        : m_impl(new Impl())
    {
    }

    GameConfigurationProvider::~GameConfigurationProvider()
    {
    }

    unsigned int GameConfigurationProvider::GetColumns() const
    {
        return m_impl->m_columns;
    }

    unsigned int GameConfigurationProvider::GetRows() const
    {
        return m_impl->m_rows;
    }

    unsigned int GameConfigurationProvider::GetZombiesToKill() const
    {
        return m_impl->m_zombiesToKill;
    }

    unsigned int GameConfigurationProvider::GetGameUpdateTime() const
    {
        return m_impl->m_updateTime;
    }

    void GameConfigurationProvider::SetColumns(unsigned int columns)
    {
        m_impl->m_columns = columns;
    }

    void GameConfigurationProvider::SetRows(unsigned int rows)
    {
        m_impl->m_rows = rows;
    }

    void GameConfigurationProvider::SetZombiesToKill(unsigned int zombiesToKill)
    {
        m_impl->m_zombiesToKill = zombiesToKill;
    }

    void GameConfigurationProvider::SetGameUpdateTime(unsigned int updateTime)
    {
        m_impl->m_updateTime = updateTime;
    }
}
