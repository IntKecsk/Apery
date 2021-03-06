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
#include <QToolBar>
#include <QFileDialog>
#include <QSettings>
#include <QMessageBox>
#include <qevent.h>

#include "aperywindow.h"
#include "aperyvport.h"

AperyWindow::AperyWindow(QWidget *parent) : QMainWindow(parent), m_rffirst(nullptr)
{
    m_avp = new AperyVPort();
    setCentralWidget(m_avp);
    _setupMenu();
    _setupToolbar();
    (void)statusBar();
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
    {
        auto s = d.selectedFiles()[0];
        if(m_avp->loadImage(s))
        {
            _addRecent(s);
        }
    }
    m_fddir = d.directory().path();
}

void AperyWindow::fileOpenRecent()
{
    QAction* ac = qobject_cast<QAction*>(sender());
    if(ac)
    {
        auto s = ac->data().toString();
        if(m_avp->loadImage(s))
        {
            _upRecent(ac);
        }
        else
        {
            QMessageBox::warning(this, tr("Could not load the file"), tr("Could not load the file anymore :-("));
            _delRecent(ac, s);
        }

    }
}

void AperyWindow::dumpSimple()
{
    _dumpSources(tr("Dump simple sources"), false);
}

void AperyWindow::dumpNeumann()
{
    _dumpSources(tr("Dump Neumann sources"), true);
}

void AperyWindow::changeMode()
{
    auto a = qobject_cast<QAction*>(sender());
    if (a)
    {
        int m = a->data().toInt();
        for (int i = 0; i < 2; i++)
        {
            m_modes[i]->setChecked(i == m);
        }
        m_avp->setMode(m);
    }
}

void AperyWindow::_setupMenu()
{
    m_file = menuBar()->addMenu(tr("&File"));
    m_file->addAction(tr("&Open"), this, SLOT(fileOpen()), QKeySequence::Open);
    m_rfsep = m_file->addSeparator();

    QMenu* tools = menuBar()->addMenu(tr("&Tools"));
    QMenu* dump = tools->addMenu(tr("&Dump"));

    dump->addAction(tr("&Simple sources"), this, SLOT(dumpSimple()));
    dump->addAction(tr("&Neumann sources"), this, SLOT(dumpNeumann()));

    QMenu* help = menuBar()->addMenu(tr("&Help"));
    help->addAction(tr("About &Qt"), qApp, SLOT(aboutQt()));
}

void AperyWindow::_setupToolbar()
{
    m_tb = addToolBar(tr("Toolbar"));
    m_modes[0] = m_tb->addAction(tr("Select"), this, SLOT(changeMode()));
    m_modes[1] = m_tb->addAction(tr("Move"), this, SLOT(changeMode()));
    for (int i = 0; i < 2; i++)
    {
        m_modes[i]->setCheckable(true);
        m_modes[i]->setData(i);
    }
    m_modes[0]->setChecked(true);
}

void AperyWindow::_readSettings()
{
    QSettings settings("IntKecsk", "Apery");

    settings.beginGroup("window");
    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    settings.endGroup();

    m_rfidx = m_file->actions().size();
    auto recent = settings.value("app/recent").toStringList();
    for(const auto& s: recent)
    {
        QFileInfo fi(s);
        auto ac = new QAction(fi.fileName(), nullptr);
        ac->setData(s);
        ac->setStatusTip(s);
        connect(ac, SIGNAL(triggered(bool)), this, SLOT(fileOpenRecent()));
        m_rfactions.insert(s, ac);
        m_file->addAction(ac);
    }

    if(!recent.empty())
    {
        m_rffirst = m_file->actions().at(m_rfidx);
        m_rfsep->setVisible(true);
    }
    else
    {
        m_rfsep->setVisible(false);
    }

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

    QStringList recent;
    auto acs = m_file->actions();
    for(int i=m_rfidx; i<acs.size(); i++)
    {
        recent.append(acs.at(i)->data().toString());
    }
    settings.setValue("app/recent", recent);
}

void AperyWindow::_addRecent(const QString& s)
{
    QFileInfo fi(s);
    auto cfp = fi.canonicalFilePath();
    auto ac = m_rfactions.value(cfp, nullptr);
    if(ac)
        return _upRecent(ac);

    ac = new QAction(fi.fileName(), nullptr);
    ac->setData(fi.canonicalFilePath());
    ac->setStatusTip(fi.canonicalFilePath());
    connect(ac, SIGNAL(triggered(bool)), this, SLOT(fileOpenRecent()));
    m_rfactions.insert(cfp, ac);
    m_file->insertAction(m_rffirst, ac);
    m_rffirst = ac;
    m_rfsep->setVisible(true);
    if(m_rfactions.size() > RECENT_FILE_LIST_SIZE)
    {
        auto dac = m_file->actions().last();
        m_rfactions.remove(dac->data().toString());
        m_file->removeAction(dac);
        delete dac;
    }
}

void AperyWindow::_delRecent(QAction* ac, const QString& s)
{
    m_rfactions.remove(s);
    m_file->removeAction(ac);
    if(m_rfactions.empty())
    {
        m_rffirst = nullptr;
        m_rfsep->setVisible(true);
    }
    else if(ac == m_rffirst)
        m_rffirst = m_file->actions().at(m_rfidx);
    delete ac;
}

void AperyWindow::_upRecent(QAction* ac)
{
    if(ac != m_rffirst)
    {
        m_file->removeAction(ac);
        m_file->insertAction(m_rffirst, ac);
        m_rffirst = ac;
    }
}

void AperyWindow::_dumpSources(const QString& caption, bool nmn)
{
    QFileDialog d(nullptr, caption, m_fddir);
    d.setFileMode(QFileDialog::AnyFile);
    d.setAcceptMode(QFileDialog::AcceptSave);
    if (d.exec())
    {
        if (!m_avp->dumpSources(d.selectedFiles()[0], nmn))
        {
            QMessageBox::warning(this, tr("Could not save the file"), tr("Could not save the file"));
        }
    }
}
