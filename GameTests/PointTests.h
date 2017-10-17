#pragma once
#include "TestCollector.h"
#include "Game/Model/Point.h"

class PointTests
    : public QObject
{
    Q_OBJECT

public:
    PointTests();
    virtual ~PointTests();

private slots:
    void SetsCorrectCoordinates();
    void EqualityTestCase1();
    void EqualityTestCase2();
    void EqualityTestCase3();
    void LessThanTestCase1();
    void LessThanTestCase2();
    void LessThanTestCase3();
    void LessThanTestCase4();
    void ConvertsPointToString();

};
ADD_TEST(PointTests)
