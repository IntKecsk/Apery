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

#include "cells.h"

constexpr tiledes NC = {0, 0, 0, 0};

namespace Tile
{

enum Type
{
    M = 0,
    KL = 1,
    KJ = 2,
    Q = 3,
    k = 4,
    qq = 5,
    qp = 6
};

}

const gscell_def gcd[8] = {
    {9, 2, 2, {
        {5, 0, 0, Tile::M},
        {3, 0, 0, Tile::KJ},
        {0, 0, 0, Tile::k},
        {7, 0, 0, Tile::KL},
        {0, 2, 2, Tile::M},
        {2, 2, 2, Tile::M},
        {4, 2, 2, Tile::M},
        {6, 2, 2, Tile::M},
        {8, 2, 2, Tile::M}
    }}, //N
    {9, 3, 3, {
        {5, 0, 0, Tile::Q},
        {2, 0, 0, Tile::qp},
        {8, 0, 0, Tile::qq},
        {2, 2, 0, Tile::KJ},
        {8, 0, 2, Tile::KL},
        {4, 3, 2, Tile::Q},
        {1, 3, 2, Tile::qp},
        {6, 2, 3, Tile::Q},
        {9, 2, 3, Tile::qq}
    }}, //W
    {8, 3, 3, {
        {2, 2, 0, Tile::Q},
        {9, 2, 0, Tile::qp},
        {8, 0, 2, Tile::Q},
        {1, 0, 2, Tile::qq},
        {4, 3, 2, Tile::Q},
        {1, 3, 2, Tile::qp},
        {6, 2, 3, Tile::Q},
        {9, 2, 3, Tile::qq},
        NC
    }}, //V
    {8, 3, 3, {
        {0, 1, 0, Tile::qq},
        {0, 0, 1, Tile::qp},
        {6, 3, 2, Tile::M},
        {4, 3, 2, Tile::KJ},
        {1, 3, 2, Tile::k},
        {4, 2, 3, Tile::M},
        {6, 2, 3, Tile::KL},
        {9, 2, 3, Tile::k},
        NC
    }}, //O
    {9, 3, 2, {
        {5, 0, 0, Tile::KJ},
        {2, 0, 0, Tile::k},
        {9, 0, 0, Tile::KL},
        {7, 0, 0, Tile::M},
        {3, 2, 0, Tile::qp},
        {7, 1, 2, Tile::KJ},
        {0, 3, 2, Tile::Q},
        {7, 3, 2, Tile::qp},
        {3, 3, 2, Tile::qq}
    }}, //S
    {7, 3, 2, {
        {5, 0, 0, Tile::KJ},
        {2, 0, 0, Tile::k},
        {9, 0, 0, Tile::KL},
        {7, 0, 0, Tile::M},
        {3, 2, 0, Tile::qp},
        {7, 1, 2, Tile::Q},
        {4, 1, 2, Tile::qp},
        NC,
        NC
    }}, //F
    {7, 3, 2, {
        {5, 0, 0, Tile::M},
        {3, 0, 0, Tile::M},
        {1, 0, 0, Tile::M},
        {9, 0, 0, Tile::M},
        {7, 0, 0, Tile::M},
        {3, 2, 0, Tile::qp},
        {5, 2, 2, Tile::qq},
        NC,
        NC
    }}, //B
    {8, 3, 3, {
        {0, 1, 0, Tile::qq},
        {8, 0, 2, Tile::Q},
        {1, 0, 2, Tile::qq},
        {6, 3, 2, Tile::M},
        {4, 3, 2, Tile::KJ},
        {1, 3, 2, Tile::k},
        {6, 2, 3, Tile::Q},
        {9, 2, 3, Tile::qq},
        NC
    }}  //Q
};
