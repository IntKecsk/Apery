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

#include "ptdefs.h"
#include "common/cells.h"
#include "rhombdrawer.h"
#include "rhombpixmaps.h"

RhombDrawer::RhombDrawer(RhombPixmaps* rpx, QPaintDevice* device) :
    QPainter(device), m_rpx(rpx)
{
}

int xs[10] = {DX, YIX, YOX, -XOX, -XIX, -DX, -YIX, -YOX, XOX, XIX};
int ys[10] = {DY, YIY, YOY, -XOY, -XIY, -DY, -YIY, -YOY, XOY, XIY};

/*Todo: rewrite sizes using XI* XO* and DX */
int dxf[10] = {  0,   0,  -7, -19, -31, -38, -31, -19,  -7,   0};
int dyf[10] = {-14, -23, -37, -37, -23, -14,   0,   0,   0,   0};
int dxs[10] = {  0,  -7, -19, -24, -19, -14, -19, -24, -19,  -7};
int dys[10] = {-23, -23, -14, -14, -23, -23, -14,   0,   0, -14};



void RhombDrawer::drawRhomb(tiledes td, int px, int py)
{
    /*int ax, ay, bx, by;*/ //, cx, cy;
    //cx=xs[ori]/4;
    //cy=ys[ori]/4;
    /*if(skr)
    {
        ax = xs[(ori+8)%10];
        ay = ys[(ori+8)%10];
        bx = xs[(ori+2)%10];
        by = ys[(ori+2)%10];
    }
    else
    {
        ax = xs[(ori+9)%10];
        ay = ys[(ori+9)%10];
        bx = xs[(ori+1)%10];
        by = ys[(ori+1)%10];
    }*/
    if(td.att_x&1)
    {
        px+=XSX;
        py+=XSY;
    }
    if(td.att_x&2)
    {
        px+=XNX;
        py+=XNY;
    }
    if(td.att_y&1)
    {
        px+=YSX;
        py+=YSY;
    }
    if(td.att_y&2)
    {
        px+=YNX;
        py+=YNY;
    }
    if((td.ori&1)^td.narrow)
    {
        px+=OSX;
        py+=OSY;
    }
    /*drawLine(px, py, px+ax, py+ay);
    drawLine(px+ax, py+ay, px+ax+bx, py+ay+by);
    drawLine(px+ax+bx, py+ay+by, px+bx, py+by);
    drawLine(px+bx, py+by, px, py);*/
    if(td.narrow) drawPixmap(px+dxs[td.ori], py+dys[td.ori], m_rpx->pxs[td.ori]);
    else  drawPixmap(px+dxf[td.ori], py+dyf[td.ori], m_rpx->pxf[td.ori]);
}
