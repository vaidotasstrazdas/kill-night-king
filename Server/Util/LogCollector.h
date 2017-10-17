#pragma once
#include <memory>

#include "ILogger.h"

namespace Util
{
    class LogCollector
        : public ILogger
    {
    public:
        LogCollector();
        ~LogCollector();

        virtual void Log(const std::string& identificator, const std::string& message) override;

        virtual std::vector<std::string> GetLogRecords() const override;

        virtual void OnLogRecordArrived(const std::function<void(const std::string&)>& onLogRecord) override;

    private:
        struct Impl;
        std::unique_ptr<Impl> m_impl;
    };
}
