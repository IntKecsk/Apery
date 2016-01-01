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

#ifndef RHOMBDRAWER_H
#define RHOMBDRAWER_H

#include <QPainter>
#include "common/cells.h"

class RhombPixmaps;
class RhombDrawer : public QPainter
{
public:
    explicit RhombDrawer(RhombPixmaps *rpx, QPaintDevice *device = 0);
    /**
     * @brief Draw a Penrose rhomb
     * @param td
     * @param px
     * @param py
     */
    void drawRhomb(tiledes td, int px, int py);
private:
    RhombPixmaps* m_rpx;
};

#endif // RHOMBDRAWER_H
