#pragma once
#include "TestCollector.h"
#include "Game/Protocol/GameProtocol.h"

class GameProtocolTests
    : public QObject
{
    Q_OBJECT

public:
    GameProtocolTests();
    virtual ~GameProtocolTests();

private slots:
    void ResolvesNoActionForEmptyString();
    void ResolvesSingleMovementAction();
    void ResolvesActionsLineByLine();
    void ResolvesAttackAction();
};
ADD_TEST(GameProtocolTests)
