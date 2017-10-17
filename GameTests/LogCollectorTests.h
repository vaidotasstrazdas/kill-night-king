#pragma once
#include "TestCollector.h"
#include "Util/LogCollector.h"

class LogCollectorTests
    : public QObject
{
    Q_OBJECT

    public:
        LogCollectorTests();
        virtual ~LogCollectorTests();

    private slots:
        void LogsRecords();
        void NotifiesOnNewLogRecordAdded();
        void NotifiesWithCorrectRecordOnNewLogRecordAdded();

};
ADD_TEST(LogCollectorTests)
