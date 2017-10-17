#pragma once
#include <functional>
#include <string>
#include <vector>

namespace Util
{
    class ILogger
    {
    public:
        virtual ~ILogger() {}

        virtual void Log(const std::string& identificator, const std::string& message) = 0;

        virtual std::vector<std::string> GetLogRecords() const = 0;

        virtual void OnLogRecordArrived(const std::function<void(const std::string&)>& onLogRecord) = 0;
    };
}
