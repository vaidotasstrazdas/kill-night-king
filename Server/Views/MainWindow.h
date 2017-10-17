#pragma once
#include <memory>

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

namespace Views
{
    class MainWindowModel;

    class MainWindow
        : public QMainWindow
    {
        Q_OBJECT
    public:
        MainWindow(MainWindowModel& model, QWidget *parent = nullptr);
        virtual ~MainWindow();

    signals:
        void ShowLogs();

    private:
        void BindControlsToData();

    private:
        std::unique_ptr<Ui::MainWindow> m_ui;
        MainWindowModel& m_model;
    };
}
