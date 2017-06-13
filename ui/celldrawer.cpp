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
Coeffs cbAchiralProto[8] = {
    //o   i   d   o   i
    { 0,  0, -1, -1, -1}, //0
    { 0,  0, -1, -1, -1}, //2
    { 0,  0, -1, -1, -1}, //4
    {-1,  1,  0, -1, -1}, //6
    { 0,  1,  0, -2, -1}, //8
    {-1,  1,  0, -2, -1}, //10
    {-1,  2,  0, -2,  0}, //12
    {-1,  1,  0, -2,  0}  //14
};

Coeffs cbChiralProto[16] = {
    //o   i   d   o   i
    { 0,  0, -1,  0, -1}, //16
    { 0,  0, -1, -1, -1}, //17
    { 0,  0, -1,  0, -1}, //18
    { 0,  0, -1, -1, -1}, //19
    { 0,  0, -1, -1, -1}, //20
    { 0,  0, -1, -1, -1}, //21
    { 0,  1,  0,  0, -1}, //22
    { 0,  1,  0, -2, -1}, //23
    { 0,  0, -1, -1, -1}, //24
    { 0,  0, -1, -1, -1}, //25
    {-1,  2,  0,  0, -1}, //26
    {-1,  2,  0, -2, -1}, //27
    { 0,  1,  0, -2, -1}, //28
    { 0,  1,  0, -2,  0}, //29
    {-1,  1,  0, -2,  0}, //30
    {-1,  1,  0, -2, -1}  //31
};

Coeffs cbSizeProto[8] = {
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
    for(int i=0; i<8; i++)
        m_achir[i] = vec.rect(cbAchiralProto[i], cbSizeProto[i>>1]);

    for(int i=0; i<16; i++)
        m_chir[i] = vec.rect(cbChiralProto[i], cbSizeProto[4+(i>>2)]);

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

namespace
{

uint8 nmn_reflect(uint8 in)
{
    return in ^ (((in + 1) & 2) ? 3 : 0);
}

CellTile _trans(const CellTile& def, uint8 co, uint8 wx, uint8 wy)
{
    CellTile res;
    switch(co)
    {
    case 0:
        res = def;
        break;
    case 1:
        res.att_x = def.att_y;
        res.att_y = def.att_x;
        res.t.ori = (10-def.t.ori)%10;
        res.t.nmn = nmn_reflect(def.t.nmn);
        break;
    case 2:
        res.att_x = def.att_x^wx;
        res.att_y = def.att_y^wy;
        res.t.ori = (def.t.ori+5)%10;
        res.t.nmn = def.t.nmn;
        break;
    case 3:
        res.att_x = def.att_y^wy;
        res.att_y = def.att_x^wx;
        res.t.ori = (15-def.t.ori)%10;
        res.t.nmn = nmn_reflect(def.t.nmn);
        break;
    default:
        Q_UNREACHABLE();
    }
    return res;
}

} // namespace

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
    quint8 ct = (ci >> 2) & 7, co = ci & 3;
    const GSCell& c = gcd[ct];
    for (int i = 0; i < c.num; i++)
    {
        CellTile td_trans = _trans(c.tiles[i], co, c.width_x, c.width_y);
        m_rd->drawRhomb(p, td_trans.t, (state >> i) & 1, pt + _getAtt(td_trans));
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
    quint8 ct = (ci >> 2) & 7, co = ci & 3;
    const GSCell& c = gcd[ct];
    int r = 0;
    for(int i=0;i<c.num;i++)
    {
        CellTile td_trans = _trans(c.tiles[i], co, c.width_x, c.width_y);
        if (m_rd->inRhomb(n, td_trans.t,  pt + _getAtt(td_trans)))
            r |= (1 << i);
    }
    return r;
}

QRect CellDrawer::getRect(quint8 ci, QPoint pt, WN x, WN y)
{
    return m_cb.getRect(ci).translated(pt + m_cg.point(x, y));
}
