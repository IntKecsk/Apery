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
    QObject(parent), m_dim(), m_mask(), m_pix(), m_vec()
{
}

void RhombDrawer::updatePixmaps(const Vectors& vec, RhombDimSP dim, RhombMaskSP mask, RhombPixSP pix)
{
    if (vec != m_vec)
    {
        m_vec = vec;
        emit dimChanged(vec);
    }
    m_dim = std::move(dim);
    m_mask = std::move(mask);
    m_pix = std::move(pix);
}

void RhombDrawer::drawRhomb(QPainter& p, Tile td, int state, QPoint pt)
{
    p.drawPixmap(pt + m_dim->get(td).topLeft(), m_pix->get(state, td));
}
