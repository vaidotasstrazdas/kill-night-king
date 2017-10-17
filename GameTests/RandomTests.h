#pragma once
#include "TestCollector.h"
#include "Util/Random.h"

class RandomTests
    : public QObject
{
    Q_OBJECT

    public:
        RandomTests();
        virtual ~RandomTests();

    private slots:
        void RandomizerIsDecentEnough();
        void Generates12SymbolsLengthStringByDefault();
        void StringLengthCanBeSpcified();

};
ADD_TEST(RandomTests)
