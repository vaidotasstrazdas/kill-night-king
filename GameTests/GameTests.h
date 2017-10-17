#pragma once
#include "TestCollector.h"
#include "Game/Model/Game.h"

class GameTests
    : public QObject
{
    Q_OBJECT

public:
    GameTests();
    virtual ~GameTests();

private slots:
    void EmptyGameIsInvalidByDefault();
    void GameBecomesValidWhenUnitIsInserted();
    void GetsUnitBySpecifiedPoint();
    void GameIsNotLostInitially();
    void GameCanBeLost();
    void GameIsNotWonInitially();
    void GameCanBeWon();
};
ADD_TEST(GameTests)
