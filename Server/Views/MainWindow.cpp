#include <QMessageBox>

#include "MainWindow.h"
#include "MainWindowModel.h"
#include "ui_MainWindow.h"
#include "DataBinding/DataBinder.h"

namespace Views
{
    MainWindow::MainWindow(MainWindowModel& model, QWidget *parent)
        : QMainWindow(parent)
        , m_ui(new Ui::MainWindow())
        , m_model(model)
    {
        m_ui->setupUi(this);
        this->setWindowTitle("Kill the Night King Server");

        BindControlsToData();
    }

    MainWindow::~MainWindow()
    {
    }

    void MainWindow::BindControlsToData()
    {
        DataBinder::BindControlToData(*m_ui->widthSpinBox, m_model.GetColumns(), &m_model);
        DataBinder::BindControlToData(*m_ui->heightSpinBox, m_model.GetRows(), &m_model);
        DataBinder::BindControlToData(*m_ui->zombiesToKillSpinBox, m_model.GetZombiesToKill(), &m_model);
        DataBinder::BindControlToData(*m_ui->updateTimeSpinBox, m_model.GetUpdateTime(), &m_model);

        m_ui->portEdit->setText("6666");
        DataBinder::BindControlToData(*m_ui->portEdit, m_model.GetPort(), &m_model);

        connect(m_ui->startServerBtn, &QPushButton::clicked, this, [this]
        {
            if (m_model.IsValid())
            {
                m_model.ConfigureGame();
                m_model.StartServer();
                return;
            }

            QMessageBox::warning(this, "Application Warning", "There are validation errors. Please fix them.");
        });

        m_ui->closeServerBtn->hide();
        connect(m_ui->openLogsBtn, &QPushButton::clicked, this, &MainWindow::ShowLogs);
        connect(&m_model, &MainWindowModel::FailedToStartServer, this, [this]
        {
            QMessageBox::critical(this, "Application Error", "Failed to start server. Any problem of the following could have occured: You did not gave permissions to allow connections or port is wrong/busy.");
        });

        connect(&m_model, &MainWindowModel::SuccessToStartServer, this, [this]
        {
            QMessageBox::information(this, "Application Information", "Server has started. Click 'Open Logs' button to see what's happening with your server and it's clients.");
            m_ui->closeServerBtn->show();
            m_ui->form->setDisabled(true);
        });

        connect(m_ui->closeServerBtn, &QPushButton::clicked, this, [this]
        {
            m_model.CloseServer();
            m_ui->form->setEnabled(true);
            m_ui->closeServerBtn->hide();
            QMessageBox::information(this, "Application Information", "Server has been closed.");
        });
    }
}
