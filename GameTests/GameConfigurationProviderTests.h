#pragma once
#include "TestCollector.h"
#include "Game/GameConfigurationProvider.h"

class GameConfigurationProviderTests
    : public QObject
{
    Q_OBJECT

public:
    GameConfigurationProviderTests();
    virtual ~GameConfigurationProviderTests();

private slots:
    void EverythingIsZeroByDefault();
    void ColumnsCanBeSet();
    void RowsCanBeSet();
    void ZombiesToKillCanBeSet();
    void EverythingCanBeSet();
    void GameUpdateTimeIsZeroInitially();
    void GameUpdateTimeCanBeSet();
};
ADD_TEST(GameConfigurationProviderTests)
