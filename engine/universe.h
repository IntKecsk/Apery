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

#include "cellfield.h"
#include <memory>

struct WNGrid
{
    Bilist<int32_t> xns;
    Bilist<int32_t> yns;

    WNPoint at(int x, int y)
    {
        auto xn = xns.at(x);
        auto yn = yns.at(x);
        return {{x - xn, xn}, {y - yn, yn}};
    }

    WN x(int i) const
    {
        auto xn = xns.at(i);
        return {i - xn, xn};
    }

    WN y(int i) const
    {
        auto yn = yns.at(i);
        return {i - yn, yn};
    }
};

class Generator
{
public:
    virtual uint8_t resolve(int x, int y, CellField& cf, WNGrid& wn) = 0;
    virtual bool init(CellField& cg, WNGrid& wn) = 0;
    virtual ~Generator() = 0;
};

class Universe
{
public:
    Universe(std::unique_ptr<Generator> gen): m_gen(std::move(gen))
    {
        m_valid = m_gen->init(m_cf, m_wn);
    }

    uint8_t at(int x, int y, uint32_t* states = nullptr) const
    {
        return m_cf.at(x, y, states);
    }

    uint8_t resolve(int x, int y)
    {
        return m_gen->resolve(x, y, m_cf, m_wn);
    }

    bool valid() const
    {
        return m_valid;
    }

    WN wnX(int i) const
    {
        return m_wn.x(i);
    }

    WN wnY(int i) const
    {
        return m_wn.y(i);
    }

    Range rangeX() const
    {
        return m_cf.rangeX();
    }

    Range rangeY() const
    {
        return m_cf.rangeY();
    }

private:
    CellField m_cf;
    WNGrid m_wn;
    std::unique_ptr<Generator> m_gen;
    bool m_valid;
};

#endif // UNIVERSE_H
