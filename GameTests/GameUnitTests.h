#pragma once
#include "TestCollector.h"
#include "Game/Model/GameUnit.h"

class GameUnitTests
    : public QObject
{
    Q_OBJECT

public:
    GameUnitTests();
    virtual ~GameUnitTests();

private slots:
    void IsInvalidByDefault();
    void IsValidWhenTypeIsKnown();
    void DefaultPointIsZero();

};
ADD_TEST(GameUnitTests)
