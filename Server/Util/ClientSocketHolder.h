#pragma once
#include <QTcpSocket>

#include "IClientSocketHolder.h"

namespace Util
{
    class ClientSocketHolder
        : public IClientSocketHolder
    {
    public:
        ClientSocketHolder(QTcpSocket* socket);
        virtual ~ClientSocketHolder();

        virtual void WriteBytes(const QByteArray& bytes) override;
        virtual void WhenBytesReady(const std::function<void(const QByteArray&)>& reader) override;
        virtual void Close() override;
        virtual void OnClose(const std::function<void()>& action) override;

    private:
        QTcpSocket* m_socket;
        std::function<void()> m_onClose;
    };
}
