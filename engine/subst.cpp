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

#include "subst.h"

constexpr int NN = 0;

const uint8 subst3[8][5][5] = {
    { //N
        { 8, 17, 14, NN, NN},
        {16,  2, 22, NN, NN},
        {14, 23, 10, NN, NN},
        {NN, NN, NN, NN, NN},
        {NN, NN, NN, NN, NN}
    },
    { //W
        { 8, 25, 28, 19, 31},
        {24,  0, 16,  2, 26},
        {29, 17, 14, 23, 10},
        {18,  2, 22,  2, 26},
        {30, 27, 10, 27,  6}
    },
    { //V
        { 4, 25, 28, 19, 31},
        {24,  0, 16,  2, 26},
        {29, 17, 14, 23, 10},
        {18,  2, 22,  2, 26},
        {30, 27, 10, 27,  6}
    },
    { //O
        { 4, 25,  8, 17, 14},
        {24,  0, 16,  2, 22},
        { 8, 17, 14, 23, 10},
        {16,  2, 22,  2, 26},
        {14, 23, 10, 27,  6}
    },
    { //S
        { 8, 21, 12, 19, 31},
        {24,  0, 18,  2, 26},
        {29, 17, 30, 27, 10},
        {NN, NN, NN, NN, NN},
        {NN, NN, NN, NN, NN}
    },
    { //F
        { 8, 21, 12, 19, 31},
        {24,  0, 18,  2, 26},
        {29, 17, 30, 27,  6},
        {NN, NN, NN, NN, NN},
        {NN, NN, NN, NN, NN}
    },
    { //B
        { 8, 21, 12, 19, 31},
        {20,  0, 18,  2, 26},
        {12, 19, 10, 27, 6},
        {NN, NN, NN, NN, NN},
        {NN, NN, NN, NN, NN}
    },
    { //Q
        { 4, 25,  8, 17, 14},
        {24,  0, 16,  2, 22},
        {29, 17, 14, 23, 10},
        {18,  2, 22,  2, 26},
        {30, 27, 10, 27,  6}
    },
};
