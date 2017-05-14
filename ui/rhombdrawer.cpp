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

#include <QPainter>

#include "common/cells.h"
#include "rhombdrawer.h"

RhombDrawer::RhombDrawer(QObject *parent):
    QObject(parent), m_dim(), m_bmp(), m_pix(), m_vec()
{
}

void RhombDrawer::updatePixmaps(const Vectors& vec, RhombDim dim, RhombBmp bmp, RhombPix pix)
{
    if (vec != m_vec)
    {
        m_vec = vec;
        emit dimChanged(vec);
    }
    m_dim = std::move(dim);
    m_bmp = std::move(bmp);
    m_pix = std::move(pix);
}

void RhombDrawer::drawRhomb(QPainter& p, tiledes td, QPoint pt)
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
    /*drawLine(px, py, px+ax, py+ay);
    drawLine(px+ax, py+ay, px+ax+bx, py+ay+by);
    drawLine(px+ax+bx, py+ay+by, px+bx, py+by);
    drawLine(px+bx, py+by, px, py);*/
    p.drawPixmap(pt + m_dim->get(td.ori, td.nmn).topLeft(), m_pix->get(td.ori, td.nmn));
}
