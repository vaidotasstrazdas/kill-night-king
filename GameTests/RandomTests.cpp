#include <QString>
#include <QtTest>

#include "RandomTests.h"

RandomTests::RandomTests()
{
}

RandomTests::~RandomTests()
{
}

void RandomTests::RandomizerIsDecentEnough()
{
    // Arrange
    const unsigned int stringsToGenerate = 1000;

    // Act
    std::set<std::string> uniqueStrings;
    for (unsigned int i = 0; i < stringsToGenerate; i++)
        uniqueStrings.insert(Util::Random::GenerateRandomString());

    // Assert - Should generate exactly 1000 different strings, since symbols set is big enough.
    QVERIFY(1000 == uniqueStrings.size());
}

void RandomTests::Generates12SymbolsLengthStringByDefault()
{
    // Act & Assert
    QVERIFY(12 == Util::Random::GenerateRandomString().length());
}

void RandomTests::StringLengthCanBeSpcified()
{
    // Arrange
    const unsigned int stringLength = 100;

    // Act & Assert
    QVERIFY(stringLength == Util::Random::GenerateRandomString(stringLength).length());
}
