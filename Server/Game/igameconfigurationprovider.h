#pragma once

namespace Game
{
    class IGameConfigurationProvider
    {
    public:
        virtual ~IGameConfigurationProvider() {}

        virtual unsigned int GetColumns() const = 0;
        virtual unsigned int GetRows() const = 0;
        virtual unsigned int GetZombiesToKill() const = 0;
        virtual unsigned int GetGameUpdateTime() const = 0;

        virtual void SetColumns(unsigned int columns) = 0;
        virtual void SetRows(unsigned int rows) = 0;
        virtual void SetZombiesToKill(unsigned int zombiesToKill) = 0;
        virtual void SetGameUpdateTime(unsigned int updateTime) = 0;
    };
}
