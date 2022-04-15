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

#ifndef APERY_CELLS_H
#define APERY_CELLS_H

#include <cstdint>
#include <array>
#include "defs.h"

/** Tile description */
struct Tile
{
    uint8_t ori; ///< Tile orientation
    uint8_t nmn; ///< von Neumann neighbourhood type
};

/** Tile as part of a GS cell */
struct CellTile
{
    Tile t;
    uint8_t att_x; ///< X attachment point within a cell
    uint8_t att_y; ///< Y attachment point within a cell
};

/** GS-cell definition structure */
struct CellDefinition
{
    uint8_t num; ///< Number of tiles in the cell
    uint8_t width_x; ///< X width descriptor
    uint8_t width_y; ///< Y width descriptor
    std::array<CellTile, Cell::MAX_TILES> tiles; ///< Tile descriptors
};

/** Specific GS-cell definitions */
extern const std::array<CellDefinition, Cell::NUM_TYPES> cell_def;

#endif // CELLS_H
