#pragma once
#include "ILogger.h"

namespace Util
{
    class DebugLogger
        : public ILogger
    {
    public:
        DebugLogger();
        virtual ~DebugLogger();

        virtual void Log(const std::string& identificator, const std::string& message) override;

        virtual std::vector<std::string> GetLogRecords() const override;

        virtual void OnLogRecordArrived(const std::function<void(const std::string&)>& onLogRecord) override;
    };
}
