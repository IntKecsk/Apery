#-------------------------------------------------
#
# Project created by QtCreator 2014-07-27T20:43:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Apery
TEMPLATE = app
CONFIG += c++14


SOURCES += main.cpp\
    common/cells.cpp \
    ui/aperyvport.cpp \
    ui/rhombdrawer.cpp \
    ui/celldrawer.cpp \
    engine/universe.cpp \
    engine/subst.cpp \
    engine/storage.cpp \
    ui/aperywindow.cpp \
    ui/dimensions.cpp \
    ui/rhombloader.cpp

HEADERS += \
    common/cells.h \
    ui/aperyvport.h \
    ui/rhombdrawer.h \
    ui/celldrawer.h \
    engine/universe.h \
    common/types.h \
    engine/subst.h \
    engine/storage.h \
    engine/quadtree.h \
    ui/aperywindow.h \
    ui/dimensions.h \
    ui/rhombloader.h

RESOURCES += \
    rsrc/masks.qrc
