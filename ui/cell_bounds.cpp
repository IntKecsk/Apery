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

#include "cell_bounds.h"

QRect achir_bounds[8] = {
    {-24, -37, 115, 75}, //0
    {-24, -37, 115, 75}, //2
    {-24, -37, 113, 75}, //4
    {12, -37, 113, 75},  //6
    {19, -60, 70, 121},  //8
    {12, -60, 70, 121},  //10
    {31, -46, 58, 93},   //12
    {12, -46, 58, 93}    //14
};
QRect chir_bounds[16] = {
    {-24, -14, 132, 52}, //16
    {-24, -37, 132, 52}, //17
    {-24, -14, 132, 52}, //18
    {-24, -37, 132, 52}, //19
    {-24, -37, 89, 75},  //20
    {-24, -37, 89, 75},  //21
    {19, -14, 89, 75},   //22
    {19, -60, 89, 75},   //23
    {-24, -37, 77, 75},  //24
    {-24, -37, 77, 75},  //25
    {31, -14, 77, 75},   //26
    {31, -60, 77, 75},   //27
    {19, -60, 70, 107},  //28
    {19, -46, 70, 107},  //29
    {12, -46, 70, 107},  //30
    {12, -60, 70, 107}   //31
};

QRect width_bounds[2][2] = {
    {
        {-24, -60, 149, 121}, // xWyW
        {-24, -60, 132, 98}   // xNyW

    },
    {
        {-24, -37, 132, 98},  // xWyN
        {-24, -37, 115, 75}   // xNyN
    }
};

QRect getRect(quint8 ci)
{
    ci&=31;
    if(ci<16) return achir_bounds[ci>>1];
    else return chir_bounds[ci-16];
}
