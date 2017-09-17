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

#ifndef CELLS_H
#define CELLS_H

#include "types.h"

/** Tile description */
struct Tile
{
    uint8 ori; ///< Tile orientation
    uint8 nmn; ///< von Neumann neighbourhood type
};

/** Tile as part of a GS cell */
struct CellTile
{
    Tile t;
    uint8 att_x; ///< X attachment point within a cell
    uint8 att_y; ///< Y attachment point within a cell
};

/** GS-cell definition structure */
struct GSCell
{
    uint8 num; ///< Number of tiles in the cell
    uint8 width_x; ///< X width descriptor
    uint8 width_y; ///< Y width descriptor
    CellTile tiles[9]; ///< Tile descriptors
};

/** Specific GS-cell definitions */
extern const GSCell gcd[8];

#endif // CELLS_H
