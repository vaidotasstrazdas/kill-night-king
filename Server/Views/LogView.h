#pragma once
#include <memory>

#include <QDialog>

namespace Ui
{
    class LogView;
}

namespace Util
{
    class ILogger;
}

namespace Views
{
    class LogView
        : public QDialog
    {
        Q_OBJECT
    public:
        LogView(Util::ILogger& logger, QWidget* parent = nullptr);
        virtual ~LogView();

    signals:
        void InitiateLogsUpdate();

    private slots:
        void UpdateLogs();

    private:
        std::unique_ptr<Ui::LogView> m_ui;
        Util::ILogger& m_logger;
    };
}
