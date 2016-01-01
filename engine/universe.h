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

#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "common/types.h"
#include "storage.h"




class NOBilist
{
public:
    int32 getN(int index) const;
    uint8 getO(int index) const;
    int ubound() const {return m_nng_n.count();}
    int lbound() const {return ~m_neg_n.count();}
    NOBilist& append(int32 n, uint8 o);
    NOBilist& prepend(int32 n, uint8 o);
private:
    BList<int32> m_nng_n; //Nonnegative
    BList<uint8> m_nng_o;
    BList<int32> m_neg_n; //Negative
    BList<uint8> m_neg_o;
};

class Universe
{
public:
    Universe(uint8 pivot, int32 pivx, int32 pivy, quint8 strans);
    uint8 at(int x, int y) const;
    WN wnX(int x) const {return _getWN(m_nox, x);}
    WN wnY(int y) const {return _getWN(m_noy, y);}
    void resolveWN(int x, int y);
    uint8 resolveCell(int x, int y);
    Range rangeX() const {return Range{m_nox.lbound()+1, m_nox.ubound()};}
    Range rangeY() const {return Range{m_noy.lbound()+1, m_noy.ubound()};}
    bool isValid() const {return m_root;}
private:
    Universe(const Universe& o) = delete;
    NOBilist m_nox; ///< X N and O
    NOBilist m_noy; ///< Y N and O

    int32 m_pivx; ///< Pivot X
    int32 m_pivy; ///< Pivot Y
    uint8 m_strans; ///< Substitution transformation

    qtnode* m_root; ///< Quad-tree root
    uint8 m_rlev; ///< Root level
    int32 m_ux; ///< Lower x for region described by root
    int32 m_uy; ///< Lower y for region described by root

    /*
    static constexpr int CH_SIZE = 29; ///< Cache chain capacity
    qtnode* m_cchain[CH_SIZE]; ///< Cache chain
    quint8 m_chl; ///< Current cache chain length
    quint32 m_prind_x; ///< Previous relative index: x
    quint32 m_prind_y; ///< Previous relative index: y
    */
    BList<ebrick> m_bricks;
    BList<innode> m_innodes;
    void _resolveWNCoord(NOBilist& wnl, int32 piv, NOBilist& sec, int32 spiv, int index);
    void _setCell(int x, int y, uint8 ci);
    WN _getWN(const NOBilist &wnl, int index) const;
    innode* _getInNode();
    ebrick* _getEBrick();
    static uint8 _getSubst(uint8 ct, int x, int y, int lenx, int leny, uint8 ori);
};

#endif // UNIVERSE_H
