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

#include "cells.h"

constexpr tiledes NC = {0, 0, 0, false};
constexpr bool WIDE = false;
constexpr bool NARROW = true;

const gscell_def gcd[8] = {
    {9, 2, 2, {
        {5, 0, 0, WIDE},
        {3, 0, 0, WIDE},
        {0, 0, 0, NARROW},
        {7, 0, 0, WIDE},
        {0, 2, 2, WIDE},
        {2, 2, 2, WIDE},
        {4, 2, 2, WIDE},
        {6, 2, 2, WIDE},
        {8, 2, 2, WIDE}
    }}, //N
    {9, 3, 3, {
        {5, 0, 0, WIDE},
        {2, 0, 0, NARROW},
        {8, 0, 0, NARROW},
        {2, 2, 0, WIDE},
        {8, 0, 2, WIDE},
        {4, 3, 2, WIDE},
        {1, 3, 2, NARROW},
        {6, 2, 3, WIDE},
        {9, 2, 3, NARROW}
    }}, //W
    {8, 3, 3, {
        {2, 2, 0, WIDE},
        {9, 2, 0, NARROW},
        {8, 0, 2, WIDE},
        {1, 0, 2, NARROW},
        {4, 3, 2, WIDE},
        {1, 3, 2, NARROW},
        {6, 2, 3, WIDE},
        {9, 2, 3, NARROW},
        NC
    }}, //V
    {8, 3, 3, {
         {0, 1, 0, NARROW},
         {0, 0, 1, NARROW},
         {6, 3, 2, WIDE},
         {4, 3, 2, WIDE},
         {1, 3, 2, NARROW},
         {4, 2, 3, WIDE},
         {6, 2, 3, WIDE},
         {9, 2, 3, NARROW},
         NC
    }}, //O
    {9, 3, 2, {
         {5, 0, 0, WIDE},
         {2, 0, 0, NARROW},
         {9, 0, 0, WIDE},
         {7, 0, 0, WIDE},
         {3, 2, 0, NARROW},
         {7, 1, 2, WIDE},
         {0, 3, 2, WIDE},
         {7, 3, 2, NARROW},
         {3, 3, 2, NARROW}
    }}, //S
    {7, 3, 2, {
         {5, 0, 0, WIDE},
         {2, 0, 0, NARROW},
         {9, 0, 0, WIDE},
         {7, 0, 0, WIDE},
         {3, 2, 0, NARROW},
         {7, 1, 2, WIDE},
         {4, 1, 2, NARROW},
         NC,
         NC
    }}, //F
    {7, 3, 2, {
         {5, 0, 0, WIDE},
         {3, 0, 0, WIDE},
         {1, 0, 0, WIDE},
         {9, 0, 0, WIDE},
         {7, 0, 0, WIDE},
         {3, 2, 0, NARROW},
         {5, 2, 2, NARROW},
         {6, 2, 2, WIDE},
         {8, 2, 2, WIDE}
    }}, //B
    {8, 3, 3, {
         {0, 1, 0, NARROW},
         {8, 0, 2, WIDE},
         {1, 0, 2, NARROW},
         {6, 3, 2, WIDE},
         {4, 3, 2, WIDE},
         {1, 3, 2, NARROW},
         {6, 2, 3, WIDE},
         {9, 2, 3, NARROW},
         NC
    }}  //Q
};
