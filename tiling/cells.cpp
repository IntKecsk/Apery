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

constexpr CellTile NC = {{0, 0}, 0, 0};

namespace Neumann
{

enum Type : uint8_t
{
    M = 0,
    KL = 1,
    KJ = 2,
    Q = 3,
    k = 4,
    qq = 5,
    qp = 6
};

uint8_t reflect(uint8_t in)
{
    return in ^ (((in + 1) & 2) ? 3 : 0);
}

}

CellTile CellTile::trans(uint8_t co, uint8_t wx, uint8_t wy) const
{
    CellTile res;
    switch(co)
    {
    case 0:
        return *this;
    case 1:
        res.att_x = att_y;
        res.att_y = att_x;
        res.t.ori = (10 - t.ori) % 10;
        res.t.nmn = Neumann::reflect(t.nmn);
        break;
    case 2:
        res.att_x = att_x ^ wx;
        res.att_y = att_y ^ wy;
        res.t.ori = (t.ori + 5) % 10;
        res.t.nmn = t.nmn;
        break;
    case 3:
        res.att_x = att_y ^ wy;
        res.att_y = att_x ^ wx;
        res.t.ori = (15 - t.ori) % 10;
        res.t.nmn = Neumann::reflect(t.nmn);
        break;
    default:
        break; // TODO: throw
    }
    return res;
}

const GSCellDef gcd[8] = {
    {9, 2, 2, {
        {{5, Neumann::M},  0, 0},
        {{3, Neumann::KJ}, 0, 0},
        {{0, Neumann::k},  0, 0},
        {{7, Neumann::KL}, 0, 0},
        {{0, Neumann::M},  2, 2},
        {{2, Neumann::M},  2, 2},
        {{4, Neumann::M},  2, 2},
        {{6, Neumann::M},  2, 2},
        {{8, Neumann::M},  2, 2}
    }}, //N
    {9, 3, 3, {
        {{5, Neumann::Q},  0, 0},
        {{2, Neumann::qp}, 0, 0},
        {{8, Neumann::qq}, 0, 0},
        {{2, Neumann::KJ}, 2, 0},
        {{8, Neumann::KL}, 0, 2},
        {{4, Neumann::Q},  3, 2},
        {{1, Neumann::qp}, 3, 2},
        {{6, Neumann::Q},  2, 3},
        {{9, Neumann::qq}, 2, 3}
    }}, //W
    {8, 3, 3, {
        {{2, Neumann::Q},  2, 0},
        {{9, Neumann::qp}, 2, 0},
        {{8, Neumann::Q},  0, 2},
        {{1, Neumann::qq}, 0, 2},
        {{4, Neumann::Q},  3, 2},
        {{1, Neumann::qp}, 3, 2},
        {{6, Neumann::Q},  2, 3},
        {{9, Neumann::qq}, 2, 3},
        NC
    }}, //V
    {8, 3, 3, {
        {{0, Neumann::qq}, 1, 0},
        {{0, Neumann::qp}, 0, 1},
        {{6, Neumann::M},  3, 2},
        {{4, Neumann::KJ}, 3, 2},
        {{1, Neumann::k},  3, 2},
        {{4, Neumann::M},  2, 3},
        {{6, Neumann::KL}, 2, 3},
        {{9, Neumann::k},  2, 3},
        NC
    }}, //O
    {9, 3, 2, {
        {{5, Neumann::KJ}, 0, 0},
        {{2, Neumann::k},  0, 0},
        {{9, Neumann::KL}, 0, 0},
        {{7, Neumann::M},  0, 0},
        {{3, Neumann::qp}, 2, 0},
        {{7, Neumann::KJ}, 1, 2},
        {{0, Neumann::Q},  3, 2},
        {{7, Neumann::qp}, 3, 2},
        {{3, Neumann::qq}, 3, 2}
    }}, //S
    {7, 3, 2, {
        {{5, Neumann::KJ}, 0, 0},
        {{2, Neumann::k},  0, 0},
        {{9, Neumann::KL}, 0, 0},
        {{7, Neumann::M},  0, 0},
        {{3, Neumann::qp}, 2, 0},
        {{7, Neumann::Q},  1, 2},
        {{4, Neumann::qp}, 1, 2},
        NC,
        NC
    }}, //F
    {7, 3, 2, {
        {{5, Neumann::M},  0, 0},
        {{3, Neumann::M},  0, 0},
        {{1, Neumann::M},  0, 0},
        {{9, Neumann::M},  0, 0},
        {{7, Neumann::M},  0, 0},
        {{3, Neumann::qp}, 2, 0},
        {{5, Neumann::qq}, 2, 2},
        NC,
        NC
    }}, //B
    {8, 3, 3, {
        {{0, Neumann::qq}, 1, 0},
        {{8, Neumann::Q},  0, 2},
        {{1, Neumann::qq}, 0, 2},
        {{6, Neumann::M},  3, 2},
        {{4, Neumann::KJ}, 3, 2},
        {{1, Neumann::k},  3, 2},
        {{6, Neumann::Q},  2, 3},
        {{9, Neumann::qq}, 2, 3},
        NC
    }}  //Q
};
