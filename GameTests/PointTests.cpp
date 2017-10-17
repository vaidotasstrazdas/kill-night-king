#include "PointTests.h"

PointTests::PointTests()
{
}

PointTests::~PointTests()
{
}

void PointTests::SetsCorrectCoordinates()
{
    // Arrange
    Game::Model::Point point(123, 456);

    // Assert
    QVERIFY(123 == point.m_x);
    QVERIFY(456 == point.m_y);
}

void PointTests::EqualityTestCase1()
{
    // Arrange
    Game::Model::Point pointOne(123, 456);
    Game::Model::Point pointTwo(123, 456);

    // Assert
    QVERIFY(pointOne == pointTwo);
    QVERIFY(!(pointOne != pointTwo));
}

void PointTests::EqualityTestCase2()
{
    // Arrange
    Game::Model::Point pointOne(123, 456);
    Game::Model::Point pointTwo(123, 123);

    // Assert
    QVERIFY(!(pointOne == pointTwo));
    QVERIFY(pointOne != pointTwo);
}

void PointTests::EqualityTestCase3()
{
    // Arrange
    Game::Model::Point pointOne(123, 456);
    Game::Model::Point pointTwo(256, 456);

    // Assert
    QVERIFY(!(pointOne == pointTwo));
    QVERIFY(pointOne != pointTwo);
}

void PointTests::LessThanTestCase1()
{
    // Arrange
    Game::Model::Point pointOne(123, 456);
    Game::Model::Point pointTwo(256, 456);

    // Assert
    QVERIFY(pointOne < pointTwo);
}

void PointTests::LessThanTestCase2()
{
    // Arrange
    Game::Model::Point pointOne(123, 456);
    Game::Model::Point pointTwo(65, 456);

    // Assert
    QVERIFY(!(pointOne < pointTwo));
}

void PointTests::LessThanTestCase3()
{
    // Arrange
    Game::Model::Point pointOne(123, 456);
    Game::Model::Point pointTwo(123, 456);

    // Assert
    QVERIFY(!(pointOne < pointTwo));
}

void PointTests::LessThanTestCase4()
{
    // Arrange
    Game::Model::Point pointOne(123, 456);
    Game::Model::Point pointTwo(123, 457);

    // Assert
    QVERIFY(pointOne < pointTwo);
}

void PointTests::ConvertsPointToString()
{
    // Arrange
    Game::Model::Point point(123, 456);

    // Assert
    QVERIFY("(123, 456)" == point.ToString());
}
