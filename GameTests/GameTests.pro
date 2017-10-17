#-------------------------------------------------
#
# Project created by QtCreator 2017-10-16T10:17:22
#
#-------------------------------------------------

QT       += testlib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = main
CONFIG   += console
CONFIG   -= app_bundle

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


SOURCES += \
    GameEngineTests.cpp \
    main.cpp \
    RandomTests.cpp \
    GameTests.cpp \
    PointTests.cpp \
    GameUnitTests.cpp \
    ClientGameChannelTests.cpp \
    GameActionTests.cpp \
    GameProtocolTests.cpp \
    GameConfigurationProviderTests.cpp \
    ViewModelObjectTests.cpp \
    ViewModelBaseTests.cpp \
    DataBinderTests.cpp \
    LogCollectorTests.cpp \
    MainWindowModelTests.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"
INCLUDEPATH += ../Server

HEADERS += \
    GameEngineTests.h \
    TestCollector.h \
    RandomTests.h \
    GameTests.h \
    PointTests.h \
    GameUnitTests.h \
    ClientGameChannelTests.h \
    GameActionTests.h \
    GameProtocolTests.h \
    GameConfigurationProviderTests.h \
    ViewModelObjectTests.h \
    ViewModelBaseTests.h \
    DataBinderTests.h \
    LogCollectorTests.h \
    MainWindowModelTests.h \
    ../Server/Views/MainWindowModel.h \
    ../Server/DataBinding/ViewModelBase.h

SOURCES += \
    ../Server/Util/Random.cpp \
    ../Server/Util/ClientSocketHolderMock.cpp \
    ../Server/Util/LogCollector.cpp \
    ../Server/Game/GameEngine.cpp \
    ../Server/Game/GameEngineMock.cpp \
    ../Server/Game/GameConfigurationProvider.cpp \
    ../Server/Game/ClientGameChannel.cpp \
    ../Server/Game/Model/Point.cpp \
    ../Server/Game/Model/Game.cpp \
    ../Server/Game/Model/GameUnit.cpp \
    ../Server/Game/Protocol/GameAction.cpp \
    ../Server/Game/Protocol/GameProtocol.cpp \
    ../Server/DataBinding/ViewModelBase.cpp \
    ../Server/DataBinding/DataBinder.cpp \
    ../Server/Server/ServerMock.cpp \
    ../Server/Views/MainWindowModel.cpp
