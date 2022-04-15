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
#include "templates.h"

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

static constexpr uint8_t reflect(uint8_t in)
{
    return in ^ (((in + 1) & 2) ? 3 : 0);
}

}

static constexpr CellTile reflect(const CellTile& src, uint8_t reflection, uint8_t wx, uint8_t wy)
{
    CellTile res{};
    switch(reflection)
    {
    case 0:
        return src;
    case 1:
        res.att_x = src.att_y;
        res.att_y = src.att_x;
        res.t.ori = (10 - src.t.ori) % 10;
        res.t.nmn = Neumann::reflect(src.t.nmn);
        break;
    case 2:
        res.att_x = src.att_x ^ wx;
        res.att_y = src.att_y ^ wy;
        res.t.ori = (src.t.ori + 5) % 10;
        res.t.nmn = src.t.nmn;
        break;
    case 3:
        res.att_x = src.att_y ^ wy;
        res.att_y = src.att_x ^ wx;
        res.t.ori = (15 - src.t.ori) % 10;
        res.t.nmn = Neumann::reflect(src.t.nmn);
        break;
    default:
        throw std::runtime_error("Illegal value for reflection");
    }
    return res;
}

constexpr CellTile cell_def_arche[Cell::NUM_ARCHETYPES][Cell::MAX_TILES] = {
    {
        {{5, Neumann::M},  0, 0},
        {{3, Neumann::KJ}, 0, 0},
        {{0, Neumann::k},  0, 0},
        {{7, Neumann::KL}, 0, 0},
        {{0, Neumann::M},  2, 2},
        {{2, Neumann::M},  2, 2},
        {{4, Neumann::M},  2, 2},
        {{6, Neumann::M},  2, 2},
        {{8, Neumann::M},  2, 2}
    }, //N
    {
        {{5, Neumann::Q},  0, 0},
        {{2, Neumann::qp}, 0, 0},
        {{8, Neumann::qq}, 0, 0},
        {{2, Neumann::KJ}, 2, 0},
        {{8, Neumann::KL}, 0, 2},
        {{4, Neumann::Q},  3, 2},
        {{1, Neumann::qp}, 3, 2},
        {{6, Neumann::Q},  2, 3},
        {{9, Neumann::qq}, 2, 3}
    }, //W
    {
        {{2, Neumann::Q},  2, 0},
        {{9, Neumann::qp}, 2, 0},
        {{8, Neumann::Q},  0, 2},
        {{1, Neumann::qq}, 0, 2},
        {{4, Neumann::Q},  3, 2},
        {{1, Neumann::qp}, 3, 2},
        {{6, Neumann::Q},  2, 3},
        {{9, Neumann::qq}, 2, 3}
    }, //V
    {
        {{0, Neumann::qq}, 1, 0},
        {{0, Neumann::qp}, 0, 1},
        {{6, Neumann::M},  3, 2},
        {{4, Neumann::KJ}, 3, 2},
        {{1, Neumann::k},  3, 2},
        {{4, Neumann::M},  2, 3},
        {{6, Neumann::KL}, 2, 3},
        {{9, Neumann::k},  2, 3}
    }, //O
    {
        {{5, Neumann::KJ}, 0, 0},
        {{2, Neumann::k},  0, 0},
        {{9, Neumann::KL}, 0, 0},
        {{7, Neumann::M},  0, 0},
        {{3, Neumann::qp}, 2, 0},
        {{7, Neumann::KJ}, 1, 2},
        {{0, Neumann::Q},  3, 2},
        {{7, Neumann::qp}, 3, 2},
        {{3, Neumann::qq}, 3, 2}
    }, //S
    {
        {{5, Neumann::KJ}, 0, 0},
        {{2, Neumann::k},  0, 0},
        {{9, Neumann::KL}, 0, 0},
        {{7, Neumann::M},  0, 0},
        {{3, Neumann::qp}, 2, 0},
        {{7, Neumann::Q},  1, 2},
        {{4, Neumann::qp}, 1, 2}
    }, //F
    {
        {{5, Neumann::M},  0, 0},
        {{3, Neumann::M},  0, 0},
        {{1, Neumann::M},  0, 0},
        {{9, Neumann::M},  0, 0},
        {{7, Neumann::M},  0, 0},
        {{3, Neumann::qp}, 2, 0},
        {{5, Neumann::qq}, 2, 2}
    }, //B
    {
        {{0, Neumann::qq}, 1, 0},
        {{8, Neumann::Q},  0, 2},
        {{1, Neumann::qq}, 0, 2},
        {{6, Neumann::M},  3, 2},
        {{4, Neumann::KJ}, 3, 2},
        {{1, Neumann::k},  3, 2},
        {{6, Neumann::Q},  2, 3},
        {{9, Neumann::qq}, 2, 3}
    }  //Q
};

static constexpr auto fill_cell_def()
{
    std::decay_t<decltype(cell_def)> res{};
    for (int i = 0; i < Cell::NUM_TYPES; i++)
    {
        auto archetype = Cell::archetype(i);
        auto reflection = Cell::reflection(i);
        const auto& base_src = cell_def_arche_base[archetype];
        const auto& src = cell_def_arche[archetype];
        auto& dst = res[i];
        dst.num = base_src.num;
        dst.width_x = reflection & 1 ? base_src.width_y : base_src.width_x;
        dst.width_y = reflection & 1 ? base_src.width_x : base_src.width_y;
        for (int j = 0; j < base_src.num; j++)
        {
            dst.tiles[j] = reflect(src[j], reflection, base_src.width_x, base_src.width_y);
        }
    }
    return res;
}

constexpr std::array<CellDefinition, Cell::NUM_TYPES> cell_def = fill_cell_def();
