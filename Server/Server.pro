#-------------------------------------------------
#
# Project created by QtCreator 2017-10-16T09:29:14
#
#-------------------------------------------------

QT       += core gui network

# C++11 support
greaterThan(QT_MAJOR_VERSION, 4) {
    CONFIG += c++11
} else {
    QMAKE_CXXFLAGS += -std=c++0x
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        Views/MainWindow.cpp \
    Server/Server.cpp \
    Game/GameEngine.cpp \
    Game/Model/Game.cpp \
    Util/Random.cpp \
    Game/Model/Point.cpp \
    Game/Model/GameUnit.cpp \
    Game/ClientGameChannel.cpp \
    Util/ClientSocketHolderMock.cpp \
    Game/GameEngineMock.cpp \
    Util/ClientSocketHolder.cpp \
    Game/Protocol/GameAction.cpp \
    Game/Protocol/GameProtocol.cpp \
    ClientSocketThread.cpp \
    Util/DebugLogger.cpp \
    Views/MainWindowModel.cpp \
    Game/GameConfigurationProvider.cpp \
    DataBinding/DataBinder.cpp \
    DataBinding/ViewModelBase.cpp \
    Util/LogCollector.cpp \
    Server/ServerMock.cpp \
    Views/LogView.cpp

HEADERS  += Views/MainWindow.h \
    Server/Server.h \
    Game/IGameEngine.h \
    Game/Model/Game.h \
    Game/Model/GameUnit.h \
    Game/Model/GameUnitType.h \
    Game/GameEngine.h \
    Util/Random.h \
    Game/Model/IGame.h \
    Game/Model/Point.h \
    Game/ClientGameChannel.h \
    Util/IClientSocketHolder.h \
    Util/ClientSocketHolderMock.h \
    Game/GameEngineMock.h \
    Util/ClientSocketHolder.h \
    Game/Protocol/IGameProtocol.h \
    Game/Protocol/GameAction.h \
    Game/Protocol/GameActionType.h \
    Game/Protocol/GameProtocol.h \
    Game/IClientGameChannel.h \
    ClientSocketThread.h \
    Util/ILogger.h \
    Util/DebugLogger.h \
    Views/MainWindowModel.h \
    Server/IServer.h \
    Game/IGameConfigurationProvider.h \
    Game/GameConfigurationProvider.h \
    DataBinding/DataBinder.h \
    DataBinding/ViewModelBase.h \
    DataBinding/ViewModelObject.h \
    DataBinding/IViewModelObject.h \
    Util/LogCollector.h \
    Server/ServerMock.h \
    Views/LogView.h

FORMS    += Views/MainWindow.ui \
    Views/LogView.ui
