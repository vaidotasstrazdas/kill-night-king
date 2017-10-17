#include "LogCollectorTests.h"

LogCollectorTests::LogCollectorTests()
{
}

LogCollectorTests::~LogCollectorTests()
{
}

void LogCollectorTests::LogsRecords()
{
    // Arrange
    Util::LogCollector logger;

    // Act
    logger.Log("Test1", "Event1");
    logger.Log("Test2", "Event2");
    logger.Log("Test3", "Event3");

    // Assert
    const auto records = logger.GetLogRecords();
    QVERIFY("Test1: Event1" == records.at(0));
    QVERIFY("Test2: Event2" == records.at(1));
    QVERIFY("Test3: Event3" == records.at(2));
}

void LogCollectorTests::NotifiesOnNewLogRecordAdded()
{
    // Arrange
    Util::LogCollector logger;
    unsigned int timesNotified = 0;
    logger.OnLogRecordArrived([&timesNotified](const std::string&)
    {
        timesNotified++;
    });

    // Act
    logger.Log("Test1", "Event1");
    logger.Log("Test2", "Event2");
    logger.Log("Test3", "Event3");

    // Assert
    QVERIFY(3 == timesNotified);
}

void LogCollectorTests::NotifiesWithCorrectRecordOnNewLogRecordAdded()
{
    // Arrange
    Util::LogCollector logger;
    bool notified = false;

    // Act & Assert
    logger.OnLogRecordArrived([&notified](const std::string& logRecord)
    {
        notified = true;
        QVERIFY("Test: Event" == logRecord);
    });

    logger.Log("Test", "Event");
    QVERIFY(notified);
}
