#include <vector>

#include <QMutex>

#include "LogCollector.h"

namespace Util
{
    struct LogCollector::Impl
    {
        QMutex m_mutex;
        std::function<void(const std::string&)> m_onLogRecord;
        std::vector<std::string> m_logRecords;
    };

    class WriteLock
    {
    public:
        WriteLock(QMutex& mutex)
            : m_mutex(mutex)
        {
            mutex.lock();
        }

        ~WriteLock()
        {
            m_mutex.unlock();
        }

    private:
        QMutex& m_mutex;
    };

    LogCollector::LogCollector()
        : m_impl(new Impl())
    {
    }

    LogCollector::~LogCollector()
    {
    }

    void LogCollector::Log(const std::string& identificator, const std::string& message)
    {
        WriteLock lock(m_impl->m_mutex);
        const auto logRecord = identificator + ": " + message;
        m_impl->m_logRecords.push_back(logRecord);
        if (m_impl->m_onLogRecord)
            m_impl->m_onLogRecord(logRecord);
    }

    std::vector<std::string> LogCollector::GetLogRecords() const
    {
        return m_impl->m_logRecords;
    }

    void LogCollector::OnLogRecordArrived(const std::function<void(const std::string&)>& onLogRecord)
    {
        WriteLock lock(m_impl->m_mutex);
        m_impl->m_onLogRecord = onLogRecord;
    }
}
