#pragma once
#include "TestCollector.h"
#include "Game/Protocol/GameAction.h"

class GameActionTests
    : public QObject
{
    Q_OBJECT

public:
    GameActionTests();
    virtual ~GameActionTests();

private slots:
    void DefaultActionIsUnknownWithZeroPoint();
    void CanCreateActionOfSpecifiedTypeAndAffectedPoint();
};
ADD_TEST(GameActionTests)
