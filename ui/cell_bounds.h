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

#ifndef CELL_BOUNDS_H
#define CELL_BOUNDS_H

#include <QRect>

/** Bounding rectangles for achiral GS-cells */
extern QRect achir_bounds[8];
/** Bounding rectangles for chiral GS-cells */
extern QRect chir_bounds[16];

/** Bounding rectangles for undetermined cells of determined width */
extern QRect width_bounds[2][2];

/** Get bounding rectangle for a cell */
QRect getRect(quint8 ci);

#endif // CELL_BOUNDS_H

