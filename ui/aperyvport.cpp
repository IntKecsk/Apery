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


#include <QList>
#include <QPixmap>
#include <QMouseEvent>
#include <QPainter>

#include "aperyvport.h"
#include "rhombdrawer.h"
#include "celldrawer.h"
#include "dimensions.h"
#include "engine/universe.h"

#include <QDebug>
#include <QFile>

AperyVPort::AperyVPort(QWidget *parent)
    : QWidget(parent),  //QOpenGLWidget(parent)
      o(400, 400), dwx(0), dnx(0), dwy(0), dny(0), m_drag(false)
{
    m_rl = new RhombLoader(this);
    RhombDrawer* rd = new RhombDrawer();
    connect(m_rl, SIGNAL(loaded(Vectors,RhombDimSP,RhombMaskSP,RhombPixSP)),
            rd, SLOT(updatePixmaps(Vectors,RhombDimSP,RhombMaskSP,RhombPixSP)));

    m_cd = new CellDrawer(rd, this);

    m_univ = new Universe(4, 0, 0, 2);
    if(!m_univ->isValid())
        return;
    for(int i=-21; i<21; i+=3)
        for(int j=-21; j<21; j+=3)
            m_univ->resolveCell(i, j);
}

bool AperyVPort::loadImage(const QString &file)
{
    QPixmap px(file);
    if(px.isNull())
        return false;
    m_rl->load(px, 1);
    update();
    return true;
}

AperyVPort::~AperyVPort()
{
    delete m_univ;
}

void AperyVPort::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    if(!m_univ->isValid() || !m_cd->ready())
        return;

    QPainter p(this);
    QRect vp = rect();
    Range rx = m_univ->rangeX();
    Range ry = m_univ->rangeY();

    for(int x: rx)
    {
        WN wnx = m_univ->wnX(x);
        for(int y: ry)
        {
            WN wny = m_univ->wnY(y);
            quint8 ci = m_univ->at(x, y);
            if(ci)
            {
                if(m_cd->getRect(ci, o, wnx, wny).intersects(vp))
                    m_cd->drawCell(p, ci, o, wnx, wny);
            }
        }
    }
}

void AperyVPort::mousePressEvent(QMouseEvent *e)
{
    if(e->button()!=Qt::LeftButton) return e->ignore();
    m_drag = true;
    drag_start = e->pos();
    orig_o = o;
}

void AperyVPort::mouseMoveEvent(QMouseEvent *e)
{
    if(!(m_drag && (e->buttons()&Qt::LeftButton))) return e->ignore();
    o = orig_o + (e->pos()-drag_start);
    update();
}

void AperyVPort::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button()!=Qt::LeftButton) return e->ignore();
    o = orig_o + (e->pos()-drag_start);
    m_drag = false;
    update();
}
