#pragma once
#include <functional>

#include <QByteArray>

namespace Util
{
    class IClientSocketHolder
    {
    public:
        virtual ~IClientSocketHolder() {}

        virtual void WriteBytes(const QByteArray& bytes) = 0;
        virtual void WhenBytesReady(const std::function<void(const QByteArray&)>& reader) = 0;
        virtual void Close() = 0;
        virtual void OnClose(const std::function<void()>& action) = 0;
    };
}
