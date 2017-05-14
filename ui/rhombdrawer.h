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

#include <QObject>
#include <QBitmap>

#include "common/cells.h"
#include "dimensions.h"
#include "rhombloader.h"

class QPainter;

class RhombDrawer : public QObject
{
    Q_OBJECT
public:
    explicit RhombDrawer(QObject *parent = 0);
    /**
     * @brief Draw a Penrose rhomb
     * @param td
     * @param px
     * @param py
     */
    void drawRhomb(QPainter& p, tiledes td, QPoint pt);
    bool ready() const
    {
        return m_pix != nullptr;
    }

public slots:
    void updatePixmaps(const Vectors& vec, RhombDim dim, RhombBmp bmp, RhombPix pix);

signals:
    void dimChanged(const Vectors& vec);

private:
    //RhombPixmaps* m_rpx;

    /*class DimCellBoundsImpl : public DimCellBounds
    {
    public:
        Q_DECL_RELAXED_CONSTEXPR DimCellBoundsImpl(const OID& oid);
    private:
        static oidxy s_mofs[24];
        static oidxy s_msiz[8];
    };*/

    Vectors m_oid;
    /*DimCellGrid m_dcg;
    DimCellBoundsImpl m_dcb;*/

    /*struct RhombDimProto
    {
        oidxy tpt;
        oidxy spt;
        oidxy siz;
    };*/

    /*struct RhombDim
    {
        QPoint tpt;
        QRect src;
        void setFromProto(const RhombDimProto& p, const Vectors& oid)
        {
            tpt = oid.point(p.tpt);
            src = oid.rect(p.spt, p.siz);
        }
    };*/

    //static RhombDimProto s_rdf[10];
    //static RhombDimProto s_rds[10];
    RhombDim m_dim;
    RhombBmp m_bmp;
    RhombPix m_pix;
    Vectors m_vec;
};

#endif // RHOMBDRAWER_H
