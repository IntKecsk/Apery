#-------------------------------------------------
#
# Project created by QtCreator 2014-07-27T20:43:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Apery
TEMPLATE = app
CONFIG += c++17

SOURCES += main.cpp\
    common/cells.cpp \
    ui/aperyvport.cpp \
    ui/rhombdrawer.cpp \
    ui/celldrawer.cpp \
    ui/aperywindow.cpp \
    ui/dimensions.cpp \
    ui/rhombloader.cpp \
    engine/types.cpp \
    engine/universe.cpp \
    engine/deflate.cpp \
    engine/cellfield.cpp

HEADERS += \
    common/cells.h \
    ui/aperyvport.h \
    ui/rhombdrawer.h \
    ui/celldrawer.h \
    common/types.h \
    engine/quadtree.h \
    ui/aperywindow.h \
    ui/dimensions.h \
    ui/rhombloader.h \
    engine/types.h \
    engine/universe.h \
    engine/deflate.h \
    engine/cellfield.h

RESOURCES += \
    rsrc/masks.qrc
