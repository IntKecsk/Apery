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

#ifndef QUADTREE_H
#define QUADTREE_H

#include  "common/types.h"

/** base for all quad-tree nodes */
struct qtnode {};

/** Leaf node. Contains cell-types and data for 4x4 square of cells. Is at level 0 */
struct brick : public qtnode
{
    uint32_t cells[16];
};

/** Leaf node. Contains cell-types for 8x8 square of empty cells. Is at level 1 */
struct ebrick : public qtnode
{
    uint8_t ctypes[64];
};

/** Inner node */
struct innode : public qtnode
{
    qtnode* s[4];
};


constexpr size_t BRICK_SIZE = sizeof(brick);
constexpr size_t INNODE_SIZE = sizeof(innode);
static_assert(sizeof(ebrick) == BRICK_SIZE, "Brick size mismatch");
#endif // QUADTREE_H

