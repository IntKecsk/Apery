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

#ifndef APERYWINDOW_H
#define APERYWINDOW_H

#include <QMainWindow>

class AperyVPort;

class AperyWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit AperyWindow(QWidget *parent = 0);
public slots:
    void fileOpen();
protected:
    virtual void closeEvent(QCloseEvent *event) override;
private:
    AperyVPort* m_avp;
    QString m_fddir;
    void _setupMenu();
    void _readSettings();
    void _writeSettings();
};

#endif // APERYWINDOW_H
