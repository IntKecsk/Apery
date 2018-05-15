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

#include <cassert>
#include <cstring>

#include "cellfield.h"
#include "common/cells.h"
#include "deflate.h"

CellField::CellField(): //(uint8_t pivot, int32_t pivx, int32_t pivy, uint8_t strans):
    /*m_pivx(pivx), m_pivy(pivy), m_strans(strans),*/ m_rlev(1), m_ux(0), m_uy(0)
{
    /*m_root = nullptr;
    / check pivot validity
    //if(strans > 3) return;
    //uint8_t ct = (pivot>>2)&7;
    //uint8_t ori = (pivot&3)^strans;

    const GSCellDef& icd = gcd[ct];
    int lenx, leny;
    if(ori&1)
    {
        lenx = icd.width_y*2 - 1;
        leny = icd.width_x*2 - 1;
    }
    else
    {
        lenx = icd.width_x*2 - 1;
        leny = icd.width_y*2 - 1;
    }

    //if(_getSubst(ct, pivx, pivy, lenx, leny, ori)!=pivot)
        return;*/
    m_root = _getEBrick();
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

uint8_t CellField::at(int x, int y, [[maybe_unused]] uint32_t* states) const
{
    if(x < m_ux || y < m_uy)
        return 0;

    int ax = x - m_ux;
    int ay = y - m_uy;
    qtnode* n = m_root;
    int diam = 1 << (m_rlev + 2);
    if (ax >= diam || ay >= diam)
        return 0;

    for (int db = diam >> 1;db > 4;db >>= 1)
    {
        int i = 0;
        if (ax & db) {
            ax -= db;
            i++;
        }
        if (ay & db) {
            ay -= db;
            i += 2;
        }
        n = static_cast<innode*>(n)->s[i];
        if (!n)
            return 0;
    }

    return static_cast<ebrick*>(n)->ctypes[8 * ay + ax];
}

/*void Universe::resolveWN(int x, int y)
{
    //_resolveWNCoord(m_nx, m_pivx, m_ny, m_pivy, x);
    //_resolveWNCoord(m_ny, m_pivy, m_nx, m_pivx, y);
}*/

/*void Universe::_resolveWNCoord(NOBilist &wnl, int32_t piv, NOBilist &sec, int32_t spiv, int index)
{
    int lo = wnl.lbound(), hi = wnl.ubound();
    if(index > lo && index < hi) return;
    while(index<=lo)
    {
        int32_t prev_n = wnl.getN(lo+1);
        int mc = lo-2*prev_n;
        bool nar;
        switch(m_strans) // TODO: outline?
        {
        case 0:
            _resolveWNCoord(wnl, piv, sec, spiv, piv+mc);
            nar = wnl.getO(piv+mc)%2;
            break;
        case 1:
            _resolveWNCoord(sec, spiv, wnl, piv, spiv+mc);
            nar = sec.getO(spiv+mc)%2;
            break;
        case 2:
            _resolveWNCoord(wnl, piv, sec, spiv, piv-mc);
            nar = wnl.getO(piv-mc)%2;
            break;
        case 3:
            _resolveWNCoord(sec, spiv, wnl, piv, spiv-mc);
            nar = sec.getO(spiv-mc)%2;
            break;
        default:
            assert(false);
        }
        if(nar)
        {
            wnl.prepend(prev_n, 2).prepend(prev_n-1, 1).prepend(prev_n-1, 0);
            lo -= 3;
        }
        else
        {
            wnl.prepend(prev_n, 4).prepend(prev_n-1, 3).prepend(prev_n-1, 2);
            wnl.prepend(prev_n-2, 1).prepend(prev_n-2, 0);
            lo -= 5;
        }
    }
    while(index>=hi)
    {
        int32_t prev_n = wnl.getN(hi-1);
        int mc = hi-2*prev_n;
        bool nar;
        switch(m_strans)
        {
        case 0:
            _resolveWNCoord(wnl, piv, sec, spiv, piv+mc);
            nar = wnl.getO(piv+mc)%2;
            break;
        case 1:
            _resolveWNCoord(sec, spiv, wnl, piv, spiv+mc);
            nar = sec.getO(spiv+mc)%2;
            break;
        case 2:
            _resolveWNCoord(wnl, piv, sec, spiv, piv-mc);
            nar = wnl.getO(piv-mc)%2;
            break;
        case 3:
            _resolveWNCoord(sec, spiv, wnl, piv, spiv-mc);
            nar = sec.getO(spiv-mc)%2;
            break;
        default:
            assert(false);
        }
        wnl.append(prev_n, 0).append(prev_n, 1).append(prev_n+1, 2);
        hi += 3;
        if(!nar)
        {
            wnl.append(prev_n+1, 3).append(prev_n+2, 4);
            hi += 2;
        }
    }
}*/

void CellField::setCell(int x, int y, uint8_t ci)
{
    int diam = 1 << (m_rlev + 2);
    while (x < m_ux || y < m_uy)
    {
        // Extend
        innode* nroot = _getInNode();
        if(y >= m_uy)
        {
            nroot->s[1] = m_root;
            m_ux -= diam;
        }
        else if(x >= m_ux)
        {
            nroot->s[2] = m_root;
            m_uy -= diam;
        }
        else
        {
            nroot->s[3] = m_root;
            m_ux -= diam;
            m_uy -= diam;
        }
        m_root = nroot;
        m_rlev++;
        diam <<= 1;
    }
    int ax = x - m_ux;
    int ay = y - m_uy;
    while (ax >= diam || ay >= diam)
    {
        innode* nroot = _getInNode();
        nroot->s[0] = m_root;
        m_root = nroot;
        m_rlev++;
        diam <<= 1;
    }
    qtnode* n = m_root;
    for (int db=diam >> 1; db > 4; db >>= 1)
    {
        int i = 0;
        if (ax & db) {
            ax -= db;
            i++;
        }
        if (ay & db) {
            ay -= db;
            i += 2;
        }
        qtnode*& nx = static_cast<innode*>(n)->s[i];
        if (!nx)
        {
            if(db > 8)
                nx = _getInNode();
            else
                nx = _getEBrick();
        }
        n = nx;
    }
    static_cast<ebrick*>(n)->ctypes[8 * ay + ax] = ci;
    m_rx.extend(x);
    m_ry.extend(y);
}


innode* CellField::_getInNode()
{
    innode* res = reinterpret_cast<innode*>(m_innodes.push_back());
    memset(res, 0, sizeof(innode));
    return res;
}

ebrick* CellField::_getEBrick()
{
    ebrick* res = reinterpret_cast<ebrick*>(m_bricks.push_back());
    memset(res, 0, sizeof(ebrick));
    return res;
}

/*uint8_t Universe::_getSubst(uint8_t ct, int x, int y, int lenx, int leny, uint8_t ori)
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
    if(nci<16) nci&=-2;
    return nci;

}*/

/*uint8_t Universe::resolveCell(int x, int y)
{
    //qDebug() << "Resolving cell:" << x << y;
    uint8_t ci = at(x, y);
    if(ci) return ci&31;
    resolveWN(x, y);
    int32_t wnx = m_nx.getN(x);
    uint8_t wox = m_nx.getO(x);
    int32_t wny = m_ny.getN(y);
    uint8_t woy = m_ny.getO(y);
    int32_t mcox = x-2*wnx-wox%2;
    int32_t mcoy = y-2*wny-woy%2;
    int bx = x - wox, by = y - woy;
    uint8_t pci;
    // = resolveCell(1-mcox, 1-mcoy);
    switch(m_strans)
    {
    case 0:
        pci = resolveCell(m_pivx+mcox, m_pivy+mcoy);
        break;
    case 1:
        pci = resolveCell(m_pivy+mcoy, m_pivx+mcox);
        break;
    case 2:
        pci = resolveCell(m_pivx-mcox, m_pivy-mcoy);
        break;
    case 3:
        pci = resolveCell(m_pivy-mcoy, m_pivx-mcox);
        break;
    default:
        assert(false);
    }
    uint8_t ct = pci>>2, ori = pci&3;
    ori^=m_strans;
    //bool narx = m_nox.getO(1-mcox)%2;
    //bool nary = m_noy.getO(1-mcoy)%2;
    int lenx, leny;
    if(ori&1)
    {
        lenx = gcd[ct].width_y*2 - 1;
        leny = gcd[ct].width_x*2 - 1;
    }
    else
    {
        lenx = gcd[ct].width_x*2 - 1;
        leny = gcd[ct].width_y*2 - 1;
    }
    //int lenx = narx ? 3 : 5;
    //int leny = nary ? 3 : 5;
    for(int iy = 0; iy < leny; iy++)
        for(int ix = 0; ix < lenx; ix++)
        {
            uint8_t nci = _getSubst(ct, ix, iy, lenx, leny, ori);
            if(ix == wox && iy == woy) ci = nci;
            _setCell(bx+ix, by+iy, nci|128);
        }
    return ci;
}*/

