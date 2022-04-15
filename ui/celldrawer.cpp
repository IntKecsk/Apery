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

#include "rhombdrawer.h"
#include "celldrawer.h"

namespace
{
constexpr Coeffs cbOriginProto[Cell::NUM_TYPES] = {
    //o   i   d   o   i
    { 0,  0, -1, -1, -1}, //N
    { 0,  0, -1, -1, -1}, //N X
    { 0,  0, -1, -1, -1}, //W
    {-1,  1,  0, -1, -1}, //W X
    { 0,  1,  0, -2, -1}, //V
    {-1,  1,  0, -2, -1}, //V X
    {-1,  2,  0, -2,  0}, //O
    {-1,  1,  0, -2,  0}, //O X
    { 0,  0, -1,  0, -1}, //S
    { 0,  0, -1, -1, -1}, //S /
    { 0,  0, -1,  0, -1}, //S X
    { 0,  0, -1, -1, -1}, //S \`
    { 0,  0, -1, -1, -1}, //F
    { 0,  0, -1, -1, -1}, //F /
    { 0,  1,  0,  0, -1}, //F X
    { 0,  1,  0, -2, -1}, //F \`
    { 0,  0, -1, -1, -1}, //B
    { 0,  0, -1, -1, -1}, //B /
    {-1,  2,  0,  0, -1}, //B X
    {-1,  2,  0, -2, -1}, //B \`
    { 0,  1,  0, -2, -1}, //Q
    { 0,  1,  0, -2,  0}, //Q /
    {-1,  1,  0, -2,  0}, //Q X
    {-1,  1,  0, -2, -1}  //Q \`
};

constexpr Coeffs cbSizeProto[Cell::NUM_ARCHETYPES] = {
    {2, 4, 1, 2, 2},
    {1, 3, 2, 2, 2},
    {1, 2, 1, 4, 2},
    {2, 1, 1, 4, 0},
    {1, 4, 2, 1, 2},
    {1, 3, 1, 2, 2},
    {2, 2, 1, 2, 2},
    {1, 2, 1, 4, 1}
};
}

void CellGrid::update(const Vectors &vec)
{
    xs = vec.point({-1, 0, 1, 1, 0});
    xn = vec.point({1, 1, 0, 1, 1});
    xw = xs + xn;

    ys = vec.point({-1, 0, 1, -1, 0});
    yn = vec.point({1, 1, 0, -1, -1});
    yw = ys + yn;

    os = vec.point({0, 2, -1, 0, 0});
}

QPoint CellGrid::point(WN x, WN y)
{
    return xw*x.w + xn*x.n + yw*y.w + yn*y.n;
}

void CellBounds::update(const Vectors &vec)
{
    for (int i = 0; i < Cell::NUM_TYPES; i++)
        m_bytype[i] = vec.rect(cbOriginProto[i], cbSizeProto[Cell::archetype(i)]);

    // TODO: fill general rectangles
}

bool CellDrawer::ready() const
{
    return m_rd->ready();
}

CellDrawer::CellDrawer(RhombDrawer *rdr, QObject *parent): QObject(parent), m_rd(rdr)
{
    m_rd->setParent(this);
    connect(m_rd, SIGNAL(dimChanged(Vectors)), this, SLOT(updateDim(Vectors)));
}

void CellDrawer::updateDim(const Vectors &vec)
{
    m_cg.update(vec);
    m_cb.update(vec);
}

void CellDrawer::drawCell(QPainter& p, quint8 ci, int state, QPoint pt, WN x, WN y)
{
    drawCell(p, ci, state, pt + m_cg.xw*x.w + m_cg.xn*x.n + m_cg.yw*y.w + m_cg.yn*y.n);
}

QPoint CellDrawer::_getAtt(const CellTile& td)
{
    QPoint pt(0, 0);
    if(td.att_x&1)
    {
        pt+=m_cg.xs;
    }
    if(td.att_x&2)
    {
        pt+=m_cg.xn;
    }
    if(td.att_y&1)
    {
        pt+=m_cg.ys;
    }
    if(td.att_y&2)
    {
        pt+=m_cg.yn;
    }
    if((td.t.ori&1)^(td.t.nmn>>2))
    {
        pt+=m_cg.os;
    }
    return pt;
}

void CellDrawer::drawCell(QPainter& p, quint8 ci, int state, QPoint pt)
{
    const auto& c =cell_def[ci & 31];
    for (int i = 0; i < c.num; i++)
    {
        m_rd->drawRhomb(p, c.tiles[i].t, (state >> i) & 1, pt + _getAtt(c.tiles[i]));
    }
}

int CellDrawer::inCell(QPoint n, quint8 ci, QPoint pt, WN x, WN y)
{
    if (!getRect(ci, pt, x, y).contains(n))
        return 0;
    return inCell(n, ci, pt + m_cg.point(x, y));
}

int CellDrawer::inCell(QPoint n, quint8 ci, QPoint pt)
{
    const auto& c = cell_def[ci & 31];
    int r = 0;
    for (int i = 0; i < c.num; i++)
    {
        if (m_rd->inRhomb(n, c.tiles[i].t,  pt + _getAtt(c.tiles[i])))
            r |= (1 << i);
    }
    return r;
}

QRect CellDrawer::getRect(quint8 ci, QPoint pt, WN x, WN y)
{
    return m_cb.getRect(ci).translated(pt + m_cg.point(x, y));
}
