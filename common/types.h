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
typedef signed char int8;          /* 8 bit signed */
typedef unsigned char uint8;       /* 8 bit unsigned */
typedef short int16;               /* 16 bit signed */
typedef unsigned short uint16;     /* 16 bit unsigned */
typedef int int32;                 /* 32 bit signed */
typedef unsigned int uint32;       /* 32 bit unsigned */
typedef long long int64;           /* 64 bit signed */
typedef unsigned long long uint64; /* 64 bit unsigned */

struct WN
{
    int32 w;
    int32 n;
};

struct Range
{
    int32 b;
    int32 e;
};

#endif // TYPES_H

