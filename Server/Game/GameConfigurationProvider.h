#pragma once
#include <memory>

#include "IGameConfigurationProvider.h"

namespace Game
{
    class GameConfigurationProvider
        : public IGameConfigurationProvider
    {
    public:
        GameConfigurationProvider();
        virtual ~GameConfigurationProvider();

        virtual unsigned int GetColumns() const override;
        virtual unsigned int GetRows() const override;
        virtual unsigned int GetZombiesToKill() const override;
        virtual unsigned int GetGameUpdateTime() const override;

        virtual void SetColumns(unsigned int columns) override;
        virtual void SetRows(unsigned int rows) override;
        virtual void SetZombiesToKill(unsigned int zombiesToKill) override;
        virtual void SetGameUpdateTime(unsigned int updateTime) override;

    private:
        struct Impl;
        std::unique_ptr<Impl> m_impl;
    };
}
