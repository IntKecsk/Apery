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
#include "cells.h"
#include "deflate.h"

CellField::CellField(): //(uint8_t pivot, int32_t pivx, int32_t pivy, uint8_t strans):
    /*m_pivx(pivx), m_pivy(pivy), m_strans(strans),*/ m_rlev(1), m_ux(0), m_uy(0)
{
    m_root = _getEBrick();
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
