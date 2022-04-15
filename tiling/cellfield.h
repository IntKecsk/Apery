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

#ifndef APERY_CELLFIELD_H
#define APERY_CELLFIELD_H

#include "lists.h"

class CellField
{
public:
    CellField(); // (uint8_t pivot, int32_t pivx, int32_t pivy, uint8_t strans);
    uint8_t at(int x, int y, uint32_t* states = nullptr) const;
    void setCell(int x, int y, uint8_t ci);
    void expand(int x, int y);
    //WNPoint getWN(int x, int y) const;
    //void resolveWN(int x, int y);
    //uint8_t resolveCell(int x, int y);
    Range rangeX() const // {return Range{static_cast<int32_t>(m_nx.lbound()) + 1, static_cast<int32_t>(m_nx.ubound())};} // TODO: decouple from N-lists
    {
        return m_rx;
    }
    Range rangeY() const // {return Range{static_cast<int32_t>(m_ny.lbound()) + 1, static_cast<int32_t>(m_ny.ubound())};}
    {
        return m_ry;
    }
    //bool isValid() const {return m_root;}
private:
    CellField(const CellField& o) = delete;
    //Bilist<int32_t> m_nx; ///< N-characteristic for x
    //Bilist<int32_t> m_ny; ///< N-characteristic for y

    /*int32_t m_pivx; ///< Pivot X
    int32_t m_pivy; ///< Pivot Y
    uint8_t m_strans;*/ ///< Substitution transformation

    qtnode* m_root; ///< Quad-tree root
    uint8_t m_rlev; ///< Root level
    int32_t m_ux; ///< Lower x for region described by root
    int32_t m_uy; ///< Lower y for region described by root

    Range m_rx;
    Range m_ry;

    const static uint32_t zerostate = 0;
    /*
    static constexpr int CH_SIZE = 29; ///< Cache chain capacity
    qtnode* m_cchain[CH_SIZE]; ///< Cache chain
    quint8 m_chl; ///< Current cache chain length
    quint32 m_prind_x; ///< Previous relative index: x
    quint32 m_prind_y; ///< Previous relative index: y
    */
    BList<ebrick> m_bricks;
    BList<innode> m_innodes;
    //void _resolveWNCoord(NOBilist& wnl, int32_t piv, NOBilist& sec, int32_t spiv, int index);
    //WN _getWN(const NOBilist &wnl, int index) const;
    innode* _getInNode();
    ebrick* _getEBrick();
    //static uint8_t _getSubst(uint8_t ct, int x, int y, int lenx, int leny, uint8_t ori);
};

#endif // CELLGRID_H
