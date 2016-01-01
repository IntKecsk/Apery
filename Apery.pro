#-------------------------------------------------
#
# Project created by QtCreator 2014-07-27T20:43:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Apery
TEMPLATE = app
CONFIG += c++11


SOURCES += main.cpp\
    common/cells.cpp \
    ui/aperyvport.cpp \
    ui/rhombdrawer.cpp \
    ui/celldrawer.cpp \
    ui/rhombpixmaps.cpp \
    engine/universe.cpp \
    ui/cell_bounds.cpp \
    engine/subst.cpp \
    engine/storage.cpp \
    ui/aperywindow.cpp

HEADERS += \
    ui/ptdefs.h \
    common/cells.h \
    ui/aperyvport.h \
    ui/rhombdrawer.h \
    ui/celldrawer.h \
    ui/rhombpixmaps.h \
    engine/universe.h \
    ui/cell_bounds.h \
    common/types.h \
    engine/subst.h \
    engine/storage.h \
    engine/quadtree.h \
    ui/aperywindow.h

RESOURCES += \
    rsrc/masks.qrc
