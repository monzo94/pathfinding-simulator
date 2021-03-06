QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = pathfinding
TEMPLATE = app
SUBDIRS += ui
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
INCLUDEPATH += src

FORMS += \
    ui/mainwindow.ui \
    ui/helpdialog.ui \
    ui/newmapdialog.ui

HEADERS += \
    src/algorithms.hpp \
    src/helpdialog.h \
    src/mainwindow.h \
    src/newmapdialog.h \
    src/tilemapscene.h \
    src/tilemapview.h \
    src/utils.h \
    src/csvencoder.h \
    src/benchmark.h \
    src/graph.hpp \
    src/geolocationgraph.h \
    src/gridgraph.h


SOURCES += \
    src/main.cpp \
    src/helpdialog.cpp \
    src/mainwindow.cpp \
    src/newmapdialog.cpp \
    src/tilemapscene.cpp \
    src/tilemapview.cpp \
    src/utils.cpp \
    src/csvencoder.cpp \
    src/benchmark.cpp \
    src/gridgraph.cpp \
    src/geolocationgraph.cpp

RESOURCES += \
    resources.qrc

