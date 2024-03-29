#-------------------------------------------------
#
# Project created by QtCreator 2019-05-08T19:51:12
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
requires(qtConfig(combobox))
TARGET = qSnake
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        snake.cpp \
        snakewindow.cpp \
        unit.cpp \
    homepage.cpp \
    costomstyle.cpp \
    foreststyle.cpp \
    prairiestyle.cpp \
    seastyle.cpp \
    shareinfo.cpp \
    environment.cpp \
    snakeboard.cpp \
    singlesnakeboard.cpp \
    doublesnakeboard.cpp \
    aisnake.cpp \
    watchaisnakeboard.cpp \
    againstaiboard.cpp


HEADERS += \
        snake.h \
        snakewindow.h \
        unit.h \
    homepage.h \
    costomstyle.h \
    foreststyle.h \
    prairiestyle.h \
    seastyle.h \
    shareinfo.h \
    environment.h \
    snakeboard.h \
    singlesnakeboard.h \
    doublesnakeboard.h \
    aisnake.h \
    watchaisnakeboard.h \
    againstaiboard.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES     = qSnake.qrc \

DISTFILES += \
    music/background.mp3 \
    music/eat.ogg \
    music/gameover.ogg \
    music/jiayou.ogg
