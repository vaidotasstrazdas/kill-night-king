#include "ClientSocketHolder.h"

namespace Util
{
    ClientSocketHolder::ClientSocketHolder(QTcpSocket* socket)
        : m_socket(socket)
    {
    }

    ClientSocketHolder::~ClientSocketHolder()
    {
    }

    void ClientSocketHolder::WriteBytes(const QByteArray& bytes)
    {
        m_socket->write(bytes);
    }

    void ClientSocketHolder::WhenBytesReady(const std::function<void(const QByteArray&)>& reader)
    {
        QObject::connect(m_socket, &QTcpSocket::readyRead, m_socket, [this, reader]
        {
            reader(m_socket->readAll());
        });
    }

    void ClientSocketHolder::Close()
    {
        m_socket->close();
        if (m_onClose)
            m_onClose();
    }

    void ClientSocketHolder::OnClose(const std::function<void()>& action)
    {
        m_onClose = action;
    }
}
