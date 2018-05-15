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
#include "common/cells.h"
#include <cassert>

constexpr int NN = 0;

const uint8_t subst3[8][5][5] = {
    { //N
        { 8, 17, 14, NN, NN},
        {16,  2, 22, NN, NN},
        {14, 23, 10, NN, NN},
        {NN, NN, NN, NN, NN},
        {NN, NN, NN, NN, NN}
    },
    { //W
        { 8, 25, 28, 19, 31},
        {24,  0, 16,  2, 26},
        {29, 17, 14, 23, 10},
        {18,  2, 22,  2, 26},
        {30, 27, 10, 27,  6}
    },
    { //V
        { 4, 25, 28, 19, 31},
        {24,  0, 16,  2, 26},
        {29, 17, 14, 23, 10},
        {18,  2, 22,  2, 26},
        {30, 27, 10, 27,  6}
    },
    { //O
        { 4, 25,  8, 17, 14},
        {24,  0, 16,  2, 22},
        { 8, 17, 14, 23, 10},
        {16,  2, 22,  2, 26},
        {14, 23, 10, 27,  6}
    },
    { //S
        { 8, 21, 12, 19, 31},
        {24,  0, 18,  2, 26},
        {29, 17, 30, 27, 10},
        {NN, NN, NN, NN, NN},
        {NN, NN, NN, NN, NN}
    },
    { //F
        { 8, 21, 12, 19, 31},
        {24,  0, 18,  2, 26},
        {29, 17, 30, 27,  6},
        {NN, NN, NN, NN, NN},
        {NN, NN, NN, NN, NN}
    },
    { //B
        { 8, 21, 12, 19, 31},
        {20,  0, 18,  2, 26},
        {12, 19, 10, 27, 6},
        {NN, NN, NN, NN, NN},
        {NN, NN, NN, NN, NN}
    },
    { //Q
        { 4, 25,  8, 17, 14},
        {24,  0, 16,  2, 22},
        {29, 17, 14, 23, 10},
        {18,  2, 22,  2, 26},
        {30, 27, 10, 27,  6}
    },
};

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
    inline static uint8_t getSubst(uint8_t ct, int x, int y, int lenx, int leny, uint8_t ori);
    inline static int diffn(int ofs);
    inline static void resolveWNCoord(int c, WNResArg& cur, WNResArg& oth, uint8_t strans);
private:
    inline static uint8_t getWNSrc(int mc, WNResArg& cur, WNResArg& oth, uint8_t strans);
};

template<>
int DeflateImpl<TagDeflate3>::widthToLen(int w)
{
    return 2 * w - 1;
}

template<>
int DeflateImpl<TagDeflate3>::ofsToLen(uint8_t ofs)
{
    return (ofs % 2) ? 3 : 5;
}

template<>
int DeflateImpl<TagDeflate3>::getMeta(int c, int n, int ofs)
{
    return c - 2 * n - ofs % 2;
}

template<>
uint8_t DeflateImpl<TagDeflate3>::getSubst(uint8_t ct, int x, int y, int lenx, int leny, uint8_t ori)
{
    uint8_t nci;
    switch(ori)
    {
    case 0:
        nci = subst3[ct][y][x];
        break;
    case 1:
        nci = subst3[ct][x][y]^1;
        break;
    case 2:
        nci = subst3[ct][leny-y-1][lenx-x-1]^2;
        break;
    case 3:
        nci = subst3[ct][lenx-x-1][leny-y-1]^3;
        break;
    default: assert(false);
    }
    if(nci<16) nci &= -2;
    return nci;
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
    // check pivot validity

    /*m_root = _getEBrick();*/
    /*m_root = rbr;
    m_nx.append(0, 0).append(0, 1).append(1, 2);
    //m_ny.append(0, 0).append(0, 1).append(1, 2);
    if(lenx==5)
        m_nx.append(1, 3).append(2, 4);
    if(leny==5)
        m_ny.append(1, 3).append(2, 4);
    for(int x=0; x<lenx; x++)
        for(int y=0; y<leny; y++)
        {
            rbr->ctypes[8*y+x] = _getSubst(ct, x, y, lenx, leny, ori) | 128;
        }
    */
}

template<typename Tag>
bool Deflate<Tag>::init(CellField &cf, WNGrid &wn)
{
    typedef DeflateImpl<Tag> Impl;

    if(m_strans > 3)
        return false;

    uint8_t ct = (m_pivot >> 2) & 7;
    uint8_t ori = (m_pivot & 3) ^ m_strans;

    const GSCellDef& icd = gcd[ct];
    int lenx, leny;
    if(ori & 1)
    {
        lenx = Impl::widthToLen(icd.width_y);
        leny = Impl::widthToLen(icd.width_x);
    }
    else
    {
        lenx = Impl::widthToLen(icd.width_x);
        leny = Impl::widthToLen(icd.width_y);
    }

    if (Impl::getSubst(ct, m_pivx, m_pivy, lenx, leny, ori) != m_pivot)
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
            cf.setCell(x, y, Impl::getSubst(ct, x, y, lenx, leny, ori) | 128);
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
        return ci & 31;

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

    uint8_t pci = resolve(m_pivx + mcx, m_pivy + mcy, cg, wn);

    uint8_t ct = pci >> 2, ori = pci & 3;
    ori ^= m_strans;

    const GSCellDef& icd = gcd[ct];
    int lenx, leny;

    if(ori & 1)
    {
        lenx = Impl::widthToLen(icd.width_y);
        leny = Impl::widthToLen(icd.width_x);
    }
    else
    {
        lenx = Impl::widthToLen(icd.width_x);
        leny = Impl::widthToLen(icd.width_y);
    }

    int bx = x - ox, by = y - oy;

    for (int iy = 0; iy < leny; iy++)
    {
        for (int ix = 0; ix < lenx; ix++)
        {
            uint8_t nci = Impl::getSubst(ct, ix, iy, lenx, leny, ori);
            if(ix == ox && iy == oy) ci = nci;
            cg.setCell(bx + ix, by + iy, nci|128);
        }
    }

    return ci;
}

template class Deflate<TagDeflate3>;


