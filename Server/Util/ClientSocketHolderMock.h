#pragma once
#include "IClientSocketHolder.h"

namespace Util
{
    class ClientSocketHolderMock
        : public IClientSocketHolder
    {
    public:
        ClientSocketHolderMock();
        virtual ~ClientSocketHolderMock();

        virtual void WriteBytes(const QByteArray& bytes) override;
        virtual void WhenBytesReady(const std::function<void(const QByteArray&)>& reader) override;
        virtual void Close() override;
        virtual void OnClose(const std::function<void()>& action) override;

        void SetBytesReady(const QByteArray& bytesReady);
        const QByteArray& GetLastBytesWritten() const;

    private:
        QByteArray m_lastBytesWritten;
        std::function<void(const QByteArray&)> m_reader;
        std::function<void()> m_onClose;
    };
}
