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

#ifndef APERY_CELLDRAWER_H
#define APERY_CELLDRAWER_H

#include <QObject>
#include <QRect>
#include "tiling/types.h"
#include "dimensions.h"

class QPainter;
class RhombDrawer;
struct CellTile;

struct CellGrid
{
public:
    void update(const Vectors& vec);

    QPoint xs;
    QPoint xn;
    QPoint xw;
    QPoint ys;
    QPoint yn;
    QPoint yw;
    QPoint os;

    QPoint point(WN x, WN y);
};

class CellBounds
{
public:
    void update(const Vectors& vec);

    Q_DECL_RELAXED_CONSTEXPR const QRect& getRect(quint8 ci) const
    {
        ci&=31;
        return (ci<16) ? m_achir[ci>>1] : m_chir[ci-16];
    }
    constexpr const QRect& getRect(bool narx, bool nary) const
    {
        return m_wn[narx][nary];
    }

protected:
    QRect m_achir[8];
    QRect m_chir[16];
    QRect m_wn[2][2];
};

class CellDrawer : public QObject
{
    Q_OBJECT
public:
    explicit CellDrawer(RhombDrawer *rdr, QObject *parent = nullptr);

    bool ready() const;

    void drawCell(QPainter& p, quint8 ci, int state, QPoint pt, WN x, WN y);
    void drawCell(QPainter& p, quint8 ci, int state, QPoint pt);
    int inCell(QPoint n, quint8 ci, QPoint pt, WN x, WN y);
    int inCell(QPoint n, quint8 ci, QPoint pt);

    QRect getRect(quint8 ci, QPoint pt, WN x, WN y);

public slots:
    void updateDim(const Vectors& vec);

private:

    QPoint _getAtt(const CellTile& td);

    RhombDrawer* m_rd;
    CellGrid m_cg;
    CellBounds m_cb;
};

#endif // CELLDRAWER_H
