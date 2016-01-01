/************************************************************************
* Ths file is part of Apery, a Penrose tiling generator and cellular    *
* automata simulator                                                    *
*                                                                       *
* Copyright (C) 2016 Anton Sanarov                                      *
*                                                                       *
* This program is free software: you can redistribute it and/or modify  *
* it under the terms of the GNU General Public License as published by  *
* the Free Software Foundation, either version 3 of the License, or     *
* (at your option) any later version.                                   *
*                                                                       *
* This program is distributed in the hope that it will be useful,       *
* but WITHOUT ANY WARRANTY; without even the implied warranty of        *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
* GNU General Public License for more details.                          *
*                                                                       *
* You should have received a copy of the GNU General Public License     *
* along with this program.  If not, see <http://www.gnu.org/licenses/>. *
*                                                                       *
* Project website: https://intkecsk.github.io/Apery                     *
* Author: Anton Sanarov <intkecsk@yandex.ru>                            *
************************************************************************/

#include <QApplication>
#include <QMenuBar>
#include <QFileDialog>
#include <QSettings>
#include <qevent.h>

#include "aperywindow.h"
#include "aperyvport.h"

AperyWindow::AperyWindow(QWidget *parent) : QMainWindow(parent)
{
    m_avp = new AperyVPort();
    setCentralWidget(m_avp);
    _setupMenu();
    _readSettings();
}

void AperyWindow::closeEvent(QCloseEvent *event)
{
    _writeSettings();
    event->accept();
}

void AperyWindow::fileOpen()
{
    QFileDialog d;
    d.setFileMode(QFileDialog::ExistingFile);
    d.setDirectory(m_fddir);
    if(d.exec())
        m_avp->loadImage(d.selectedFiles()[0]);
    m_fddir = d.directory().path();
}

void AperyWindow::_setupMenu()
{
    QMenu* file = menuBar()->addMenu(tr("&File"));
    file->addAction(tr("&Open"), this, SLOT(fileOpen()));
    QMenu* help = menuBar()->addMenu(tr("&Help"));
    help->addAction(tr("About &Qt"), qApp, SLOT(aboutQt()));
}

void AperyWindow::_readSettings()
{
    QSettings settings("IntKecsk", "Apery");

    settings.beginGroup("window");
    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    settings.endGroup();

    m_fddir = settings.value("dialog/dir", QDir::currentPath()).toString();
}

void AperyWindow::_writeSettings()
{
    QSettings settings("IntKecsk", "Apery");

    settings.beginGroup("window");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();

    settings.setValue("dialog/dir", m_fddir);
}


