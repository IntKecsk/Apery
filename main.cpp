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
#include <QMainWindow>

#include "ui/aperywindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AperyWindow w;
    w.show();
    return a.exec();
}
