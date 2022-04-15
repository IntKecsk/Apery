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

#include "deflate.h"
#include "cells.h"
#include "templates.h"
#include <cassert>

constexpr uint8_t subst3_arche[8][5][5] = {
    { //N
        {4,  9,  7},
        {8,  1, 14},
        {7, 15,  5}
    },
    { //W
        { 4, 17, 20, 11, 23},
        {16,  0,  8,  1, 18},
        {21,  9,  7, 15,  5},
        {10,  1, 14,  1, 18},
        {22, 19,  5, 19,  3}
    },
    { //V
        { 2, 17, 20, 11, 23},
        {16,  0,  8,  1, 18},
        {21,  9,  7, 15,  5},
        {10,  1, 14,  1, 18},
        {22, 19,  5, 19,  3}
    },
    { //O
        { 2, 17,  4,  9,  7},
        {16,  0,  8,  1, 14},
        { 4,  9,  7, 15,  5},
        { 8,  1, 14,  1, 18},
        { 7, 15,  5, 19,  3}
    },
    { //S
        { 4, 13,  6, 11, 23},
        {16,  0, 10,  1, 18},
        {21,  9, 22, 19,  5}
    },
    { //F
        { 4, 13,  6, 11, 23},
        {16,  0, 10,  1, 18},
        {21,  9, 22, 19,  3}
    },
    { //B
        { 4, 13,  6, 11, 23},
        {12,  0, 10,  1, 18},
        { 6, 11,  5, 19,  3}
    },
    { //Q
        { 2, 17,  4,  9,  7},
        {16,  0,  8,  1, 14},
        {21,  9,  7, 15,  5},
        {10,  1, 14,  1, 18},
        {22, 19,  5, 19,  3}
    }
};

static constexpr int width_to_len(int w)
{
    return 2*w - 1;
}

constexpr auto fill_subst3()
{
    std::array<std::array<std::array<uint8_t, 5>, 5>, Cell::NUM_TYPES> res{};
    for (int i = 0; i < Cell::NUM_TYPES; i++)
    {
        auto archetype = Cell::archetype(i);
        auto reflection = Cell::reflection(i);
        const auto& base_src = cell_def_arche_base[archetype];
        const auto& src = subst3_arche[archetype];
        auto& dst = res[i];
        auto lenx = width_to_len(base_src.width_x);
        auto leny = width_to_len(base_src.width_y);
        for (int y = 0; y < leny; y++)
        {
            for (int x = 0; x < lenx; x++)
            {
                switch (reflection)
                {
                case 0:
                    dst[y][x] = src[y][x];
                    break;
                case 1:
                    dst[x][y] = Cell::reflect_type(src[y][x], reflection);
                    break;
                case 2:
                    dst[y][x] = Cell::reflect_type(src[leny-y-1][lenx-x-1], reflection);
                    break;
                case 3:
                    dst[x][y] = Cell::reflect_type(src[leny-y-1][lenx-x-1], reflection);
                    break;
                default:
                    break;
                }
            }
        }
    }

    return res;
}

constexpr auto subst3 = fill_subst3();

struct WNResArg
{
    int pivc;
    Bilist<int32_t>& ns;
    Bilist<uint8_t>& os;
};

template<typename Tag>
struct DeflateImpl
{
    inline static int widthToLen(int w);
    inline static int ofsToLen(uint8_t ofs);
    inline static int getMeta(int c, int n, int ofs = 0);
    inline static uint8_t getSubst(uint8_t ct, int x, int y);
    inline static int diffn(int ofs);
    inline static void resolveWNCoord(int c, WNResArg& cur, WNResArg& oth, uint8_t strans);
private:
    inline static uint8_t getWNSrc(int mc, WNResArg& cur, WNResArg& oth, uint8_t strans);
};

template<>
int DeflateImpl<TagDeflate3>::widthToLen(int w)
{
    return width_to_len(w);
}

template<>
int DeflateImpl<TagDeflate3>::ofsToLen(uint8_t ofs)
{
    return (ofs % 2) ? 3 : 5;
}

template<>
int DeflateImpl<TagDeflate3>::getMeta(int c, int n, int ofs)
{
    return c - 2*n - ofs%2;
}

template<>
uint8_t DeflateImpl<TagDeflate3>::getSubst(uint8_t ct, int x, int y)
{
    return subst3[ct][y][x];
}

template<>
int DeflateImpl<TagDeflate3>::diffn(int ofs)
{
    return ofs / 2;
}

template<typename Tag>
uint8_t DeflateImpl<Tag>::getWNSrc(int mc, WNResArg& cur, WNResArg& oth, uint8_t strans)
{
    if (strans & 2)
        mc = -mc;

    if (strans & 1)
    {
        int tc = oth.pivc + mc;
        resolveWNCoord(tc, oth, cur, strans);
        return oth.os.at(tc);
    }
    else
    {
        int tc = cur.pivc + mc;
        resolveWNCoord(tc, cur, oth, strans);
        return cur.os.at(tc);
    }
}

template<typename Tag>
void DeflateImpl<Tag>::resolveWNCoord(int c, WNResArg& cur, WNResArg& oth, uint8_t strans)
{
    int lo = cur.ns.lbound(), hi = cur.ns.ubound();
    if (c > lo && c < hi)
        return;

    while (c <= lo)
    {
        int prev_n = cur.ns.at(lo + 1);
        int mc = getMeta(lo, prev_n);
        uint8_t src = getWNSrc(mc, cur, oth, strans);
        int len = ofsToLen(src);
        int left_n = prev_n - diffn(len);
        for (int i = len - 1; i >= 0; i--)
        {
            cur.ns.push_front(left_n + diffn(i));
            cur.os.push_front(i);
        }
        lo -= len;
    }

    while (c >= hi)
    {
        int prev_n = cur.ns.at(hi - 1);
        int mc = getMeta(hi, prev_n);
        uint8_t src = getWNSrc(mc, cur, oth, strans);
        int len = ofsToLen(src);
        for (int i = 0; i < len; i++)
        {
            cur.ns.push_back(prev_n + diffn(i));
            cur.os.push_back(i);
        }
        hi += len;
    }
}



/*template<>
struct DeflateImpl<TagDeflate6>
{
};
*/

template<typename Tag>
Deflate<Tag>::Deflate(uint8_t pivot, int32_t pivx, int32_t pivy, uint8_t strans):
    DeflateBase(pivot, pivx, pivy, strans)
{
    //TODO: check pivot validity here
}

template<typename Tag>
bool Deflate<Tag>::init(CellField &cf, WNGrid &wn)
{
    typedef DeflateImpl<Tag> Impl;

    if(m_strans > 3)
        return false;

    uint8_t super_cell = Cell::reflect_type(m_pivot, m_strans);

    const auto& icd = cell_def[super_cell];

    int lenx = Impl::widthToLen(icd.width_x);
    int leny = Impl::widthToLen(icd.width_y);

    if (Impl::getSubst(super_cell, m_pivx, m_pivy) != m_pivot)
        return false;

    for (int x = 0; x < lenx; x++)
    {
        wn.xns.push_back(Impl::diffn(x));
        m_os.xos.push_back(x);
    }

    for (int y = 0; y < leny; y++)
    {
        wn.yns.push_back(Impl::diffn(y));
        m_os.yos.push_back(y);
    }

    for(int x=0; x < lenx; x++)
    {
        for(int y=0; y<leny; y++)
        {
            cf.setCell(x, y, Impl::getSubst(super_cell, x, y) | 128);
        }
    }
    return true;
}

template<typename Tag>
uint8_t Deflate<Tag>::resolve(int x, int y, CellField &cg, WNGrid &wn)
{
    typedef DeflateImpl<Tag> Impl;

    uint8_t ci = cg.at(x, y);
    if (ci)
    {
        return ci & 31;
    }

    WNResArg rax{m_pivx, wn.xns, m_os.xos};
    WNResArg ray{m_pivy, wn.yns, m_os.yos};

    Impl::resolveWNCoord(x, rax, ray, m_strans);
    Impl::resolveWNCoord(y, ray, rax, m_strans);

    uint8_t ox = m_os.xos.at(x);
    uint8_t oy = m_os.yos.at(y);
    int mcx = Impl::getMeta(x, wn.xns.at(x), ox);
    int mcy = Impl::getMeta(y, wn.yns.at(y), oy);

    if (m_strans & 1)
        std::swap(mcx, mcy);

    if (m_strans & 2)
    {
        mcx = -mcx;
        mcy = -mcy;
    }

    uint8_t pci = Cell::reflect_type(resolve(m_pivx + mcx, m_pivy + mcy, cg, wn), m_strans);

    const auto& icd = cell_def[pci];

    int lenx = Impl::widthToLen(icd.width_x);
    int leny = Impl::widthToLen(icd.width_y);

    int bx = x - ox, by = y - oy;

    for (int iy = 0; iy < leny; iy++)
    {
        for (int ix = 0; ix < lenx; ix++)
        {
            uint8_t nci = Impl::getSubst(pci, ix, iy);
            if(ix == ox && iy == oy) ci = nci;
            cg.setCell(bx + ix, by + iy, nci|128);
        }
    }

    return ci;
}

template class Deflate<TagDeflate3>;
