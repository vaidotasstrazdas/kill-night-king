#include <qdebug.h>

#include "DebugLogger.h"

namespace Util
{
    DebugLogger::DebugLogger()
    {
    }

    DebugLogger::~DebugLogger()
    {
    }

    void DebugLogger::Log(const std::string& identificator, const std::string& message)
    {
        qDebug() << identificator.c_str() << ": " << message.c_str();
    }

    std::vector<std::string> DebugLogger::GetLogRecords() const
    {
        return {};
    }

    void DebugLogger::OnLogRecordArrived(const std::function<void(const std::string&)>& onLogRecord)
    {
        // Do nothing.
    }
}
