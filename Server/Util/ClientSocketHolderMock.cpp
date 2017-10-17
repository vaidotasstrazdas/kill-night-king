#include "ClientSocketHolderMock.h"

namespace Util
{
    ClientSocketHolderMock::ClientSocketHolderMock()
    {
    }

    ClientSocketHolderMock::~ClientSocketHolderMock()
    {
    }

    void ClientSocketHolderMock::WriteBytes(const QByteArray& bytes)
    {
        m_lastBytesWritten = bytes;
    }

    void ClientSocketHolderMock::WhenBytesReady(const std::function<void(const QByteArray&)>& reader)
    {
        m_reader = reader;
    }

    void ClientSocketHolderMock::SetBytesReady(const QByteArray& bytes)
    {
        if (m_reader)
            m_reader(bytes);
    }

    const QByteArray& ClientSocketHolderMock::GetLastBytesWritten() const
    {
        return m_lastBytesWritten;
    }

    void ClientSocketHolderMock::Close()
    {
        if (m_onClose)
            m_onClose();
    }

    void ClientSocketHolderMock::OnClose(const std::function<void()>& action)
    {
        m_onClose = action;
    }
}
