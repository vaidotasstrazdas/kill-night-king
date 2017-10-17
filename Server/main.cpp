#include <QApplication>

#include "Game/Protocol/GameProtocol.h"
#include "Game/GameConfigurationProvider.h"
#include "Game/GameEngine.h"
#include "Game/ClientGameChannel.h"
#include "Util/LogCollector.h"
#include "Views/LogView.h"
#include "Views/MainWindow.h"
#include "Views/MainWindowModel.h"
#include "Server/Server.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    Game::GameConfigurationProvider gameConfigurationProvider;
    Game::Protocol::GameProtocol gameProtocol;
    Game::GameEngine gameEngine(gameProtocol, gameConfigurationProvider);
    Game::ClientGameChannel gameChannel(gameEngine);
    Util::LogCollector logger;
    Server::Server server(gameChannel, logger, gameConfigurationProvider);

    Views::MainWindowModel model(server, gameConfigurationProvider);
    Views::MainWindow mainView(model);

    QObject::connect(&mainView, &Views::MainWindow::ShowLogs, [&]
    {
        Views::LogView logView(logger, &mainView);
        logView.exec();
    });

    mainView.show();

    return application.exec();
}
