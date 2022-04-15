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
    tiling/cells.cpp \
    tiling/lists.cpp \
    tiling/universe.cpp \
    tiling/deflate.cpp \
    tiling/cellfield.cpp \
    ui/aperyvport.cpp \
    ui/rhombdrawer.cpp \
    ui/celldrawer.cpp \
    ui/aperywindow.cpp \
    ui/dimensions.cpp \
    ui/rhombloader.cpp

HEADERS += \
    tiling/types.h \
    tiling/cells.h \
    tiling/quadtree.h \
    tiling/lists.h \
    tiling/universe.h \
    tiling/deflate.h \
    tiling/cellfield.h \
    ui/aperyvport.h \
    ui/rhombdrawer.h \
    ui/celldrawer.h \
    ui/aperywindow.h \
    ui/dimensions.h \
    ui/rhombloader.h

RESOURCES += \
    rsrc/masks.qrc
