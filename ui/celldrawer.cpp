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

#include "celldrawer.h"

CellDrawer::CellDrawer(RhombPixmaps *rpx, QPaintDevice *device) : RhombDrawer(rpx, device)
{

}

void CellDrawer::drawCell(quint8 ci, int px, int py)
{
    quint8 ct=(ci>>2)&7, co=ci&3;
    const gscell_def& c = gcd[ct];
    for(int i=0;i<c.num;i++)
    {
        const tiledes& td_def = c.tiles[i];
        tiledes td_trans;
        switch(co)
        {
        case 0:
            td_trans = td_def;
            break;
        case 1:
            td_trans.att_x = td_def.att_y;
            td_trans.att_y = td_def.att_x;
            td_trans.ori = (10-td_def.ori)%10;
            td_trans.narrow = td_def.narrow;
            break;
        case 2:
            td_trans.att_x = td_def.att_x^c.width_x;
            td_trans.att_y = td_def.att_y^c.width_y;
            td_trans.ori = (td_def.ori+5)%10;
            td_trans.narrow = td_def.narrow;
            break;
        case 3:
            td_trans.att_x = td_def.att_y^c.width_y;
            td_trans.att_y = td_def.att_x^c.width_x;
            td_trans.ori = (15-td_def.ori)%10;
            td_trans.narrow = td_def.narrow;
            break;
        default:
            Q_ASSERT(0);
        }
        drawRhomb(td_trans, px, py);
    }
}
