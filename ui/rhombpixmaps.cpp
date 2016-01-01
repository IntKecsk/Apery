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

#include "rhombpixmaps.h"
#include "ptdefs.h"


/*Todo: rewrite sizes using XI* XO* and DX */
QRect regf[10] =
{
    QRect(38,23,39,29),
    QRect(38,14,32,24),
    QRect(31, 0,27,38),
    QRect(19, 0,27,38),
    QRect( 7,14,32,24),
    QRect( 0,23,39,29),
    QRect( 7,37,32,24),
    QRect(19,37,27,38),
    QRect(31,37,27,38),
    QRect(38,37,32,24)
};
QRect regs[10] =
{
    QRect( 0,14,15,47),
    QRect( 0,37,27,38),
    QRect( 7,60,44,15),
    QRect(26,60,44,15),
    QRect(50,37,27,38),
    QRect(62,14,15,47),
    QRect(50, 0,27,38),
    QRect(26, 0,44,15),
    QRect( 7, 0,44,15),
    QRect( 0, 0,27,38),
};

constexpr int WX=XOX*2+XIX*2+DX+1;
constexpr int WY=XOY*2+XIY*2+1;

RhombPixmaps::RhombPixmaps(QObject *parent) :
    QObject(parent)
{
    QString fn = ":/f%1.png", sn = ":/s%1.png";
    for(int i=0;i<5;i++)
    {
        mf[i].load(fn.arg(i));
        ms[i].load(sn.arg(i));
    }
}

void RhombPixmaps::loadPixmaps(const QPixmap &src)
{
    if(src.width()<WX || src.height()<WY) return;
    QPixmap cs[2];
    cs[0]=src.copy(0,0,77,75);
    if(src.width()>=2*WX)
        cs[1] = src.copy(77,0,77,75);
    else
        cs[1] = cs[0].transformed(QTransform(-1, 0, 0, -1, 0, 0));
    for(int i=0;i<10;i++)
    {
        pxf[i]=cs[i%2].copy(regf[i]);
        pxf[i].setMask(mf[i%5]);
        pxs[i]=cs[i%2].copy(regs[i]);
        pxs[i].setMask(ms[i%5]);
    }
}
