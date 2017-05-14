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

#ifndef DIMENSIONS_H
#define DIMENSIONS_H

#include <QPoint>
#include <QRect>

struct Coeffs
{
    int mxo;
    int mxi;
    int mxd;
    int myo;
    int myi;
};

struct RectCoeffs
{
    Coeffs ofs;
    Coeffs siz;
};

struct Vectors
{
    QPoint o;
    QPoint i;
    int d;
    QPoint point(const Coeffs& mp) const;
    QSize size(const Coeffs& mp) const;
    QRect rect(const Coeffs& ofs, const Coeffs& siz) const;
    QRect rect(const RectCoeffs& mp) const
    {
        return rect(mp.ofs, mp.siz);
    }
    bool operator!=(const Vectors& o_) const
    {
        return o != o_.o || i != o_.i || d != o_.d;
    }
};

#endif // DIMENSIONS_H
