#include "Util/ILogger.h"

#include "LogView.h"
#include "ui_LogView.h"

namespace Views
{
    LogView::LogView(Util::ILogger& logger, QWidget* parent)
        : QDialog(parent)
        , m_ui(new Ui::LogView())
        , m_logger(logger)
    {
        m_ui->setupUi(this);
        this->setModal(true);
        this->setWindowTitle("Kill the Night King Server Logs");

        UpdateLogs();
        connect(this, SIGNAL(InitiateLogsUpdate()), this, SLOT(UpdateLogs()));
        m_logger.OnLogRecordArrived([this](const std::string&)
        {
            emit InitiateLogsUpdate();
        });
    }

    LogView::~LogView()
    {
        m_logger.OnLogRecordArrived([this](const std::string&){});
    }

    void LogView::UpdateLogs()
    {
        std::string logs = "";
        for (const auto logRecord : m_logger.GetLogRecords())
            logs += logRecord + "\n";

        m_ui->logsText->setText(QString::fromStdString(logs));
    }
}
