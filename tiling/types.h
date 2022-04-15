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

#ifndef TYPES_H
#define TYPES_H

#include <cstddef>
#include <cstdint>

struct WN
{
    int32_t w;
    int32_t n;
};

struct WNPoint
{
    WN x;
    WN y;
};

struct Range
{
    struct iterator
    {
        int32_t i;
        constexpr iterator(int32_t i_): i(i_) {}
        iterator& operator++() {i++; return *this;}
        bool operator !=(const iterator& o) const {return i != o.i;}
        constexpr int32_t operator*() const {return i;}
    };

    Range(): b(INT32_MAX), e(INT32_MIN + 1)
    {
    }

    void extend(int32_t n)
    {
        if (n < b)
            b = n;

        if (n >= e)
            e = n + 1;
    }
    iterator begin() const {return b;}
    iterator end() const {return e;}

    int32_t b;
    int32_t e;
};

#endif // TYPES_H

