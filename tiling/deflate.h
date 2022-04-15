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

#ifndef DEFLATE_H
#define DEFLATE_H

#include "universe.h"

struct TagGrid
{
    Bilist<uint8_t> xos;
    Bilist<uint8_t> yos;
};

class DeflateBase : public Generator
{
protected:
    DeflateBase(uint8_t pivot, int32_t pivx, int32_t pivy, uint8_t strans):
        m_pivx(pivx), m_pivy(pivy), m_pivot(pivot), m_strans(strans)
    {
    }

    TagGrid m_os;
    int32_t m_pivx;
    int32_t m_pivy;
    uint8_t m_pivot;
    uint8_t m_strans;
    //bool m_valid = true;
};

struct TagDeflate3;
struct TagDeflate6;

template<typename Tag>
class Deflate : public DeflateBase
{
public:
    Deflate(uint8_t pivot, int32_t pivx, int32_t pivy, uint8_t strans);
    virtual bool init(CellField &cf, WNGrid &wn) override;
    virtual uint8_t resolve(int x, int y, CellField &cg, WNGrid &wn) override;
};

extern template class Deflate<TagDeflate3>;
//extern template class Deflate<TagDeflate6>;

typedef Deflate<TagDeflate3> Deflate3;
//typedef Deflate<TagDeflate6> Deflate6;

#endif // DEFLATE_H

