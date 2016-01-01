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

#ifndef PTDEFS_H
#define PTDEFS_H

//Simple vectors
constexpr int DX = 24;
constexpr int DY = 0;
constexpr int XIX = 19;
constexpr int XIY = 14;
constexpr int YIX = XIX;
constexpr int YIY = -XIY;
constexpr int XOX = 7;
constexpr int XOY = 23;
constexpr int YOX = XOX;
constexpr int YOY = -XOY;

//Narrow column & hor. attachment #2
constexpr int XNX = XIX+XOX;
constexpr int XNY = XIY+XOY;
//Hor. attachment #1
constexpr int XSX = DX-YOX;
constexpr int XSY = DY-YOY;
//Wide column
constexpr int XWX = XNX+XSX;
constexpr int XWY = XNY+XSY;

//Narrow row & vert. attachment #2
constexpr int YNX = YIX+YOX;
constexpr int YNY = YIY+YOY;
//Vert attachment #1
constexpr int YSX = DX-XOX;
constexpr int YSY = DY-XOY;
//Wide row
constexpr int YWX = YNX+YSX;
constexpr int YWY = YNY+YSY;

//Orientation correction
constexpr int OSX = XIX+YIX-DX;
constexpr int OSY = XIY+YIY-DY;

#endif // PTDEFS_H
