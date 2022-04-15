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
#include <QApplication>

#include "aperyvport.h"
#include "rhombdrawer.h"
#include "celldrawer.h"
#include "dimensions.h"
#include "tiling/universe.h"
#include "tiling/deflate.h"

#include <QDebug>
#include <QFile>

AperyVPort::AperyVPort(QWidget *parent)
    : QWidget(parent),  //QOpenGLWidget(parent)
      o(400, 400), dwx(0), dnx(0), dwy(0), dny(0), m_mode(0), m_drag(false)
{
    m_rl = new RhombLoader(this);
    RhombDrawer* rd = new RhombDrawer();
    connect(m_rl, SIGNAL(loaded(Vectors,RhombDimSP,RhombMaskSP,RhombPixSP)),
            rd, SLOT(updatePixmaps(Vectors,RhombDimSP,RhombMaskSP,RhombPixSP)));

    m_cd = new CellDrawer(rd, this);

    auto gen = std::make_unique<Deflate3>(4, 0, 0, 2);
    m_univ = new Universe(std::move(gen));
    if(!m_univ->valid())
        return;
    for(int i=-21; i<21; i+=3)
        for(int j=-21; j<21; j+=3)
            m_univ->resolve(i, j);
}

bool AperyVPort::loadImage(const QString &file)
{
    QPixmap px(file);
    if(px.isNull())
        return false;
    m_rl->load(px, 1);//2);
    update();
    return true;
}

bool AperyVPort::dumpSources(const QString &file, bool nmn)
{
    QImage img = m_rl->dump(nmn);
    return img.save(file);
}

void AperyVPort::setMode(int mode)
{
    m_mode = mode;
    switch (m_mode)
    {
    case 0:
        unsetCursor();
        break;
    case 1:
        setCursor(Qt::OpenHandCursor);
        break;
    default:
        break;
    }
}

AperyVPort::~AperyVPort()
{
    delete m_univ;
}

void AperyVPort::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    if(!m_univ->valid() || !m_cd->ready())
        return;

    QPainter p(this);
    QRect vp = rect();
    Range rx = m_univ->rangeX();
    Range ry = m_univ->rangeY();

    for (int x: rx)
    {
        WN wnx = m_univ->wnX(x);
        for (int y: ry)
        {
            WN wny = m_univ->wnY(y);
            quint8 ci = m_univ->at(x, y);
            if (ci)
            {
                if (m_cd->getRect(ci, o, wnx, wny).intersects(vp))
                {
                    int s = 0; //m_hot ? m_cd->inCell(m_hp, ci, o, wnx, wny) : 0;
                    m_cd->drawCell(p, ci, s, o, wnx, wny);
                }
            }
        }
    }
}

void AperyVPort::mousePressEvent(QMouseEvent *e)
{
    if (e->button() != Qt::LeftButton)
        return e->ignore();

    switch(m_mode)
    {
    case 0:
        m_hot = true;
        m_hp = e->pos();
        update();
        break;
    case 1:
        qApp->setOverrideCursor(Qt::ClosedHandCursor);
        m_drag = true;
        drag_start = e->pos();
        orig_o = o;
        break;
    default:
        break;
    }
}

void AperyVPort::mouseMoveEvent(QMouseEvent *e)
{
    if (!(e->buttons() & Qt::LeftButton))
        return e->ignore();

    if (m_drag)
        o = orig_o + (e->pos()-drag_start);
    else if (m_hot)
        m_hp = e->pos();

    update();
}

void AperyVPort::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() != Qt::LeftButton)
        return e->ignore();

    if (m_drag)
    {
        o = orig_o + (e->pos()-drag_start);
        m_drag = false;
        qApp->restoreOverrideCursor();
    }
    else if (m_hot)
    {
        m_hot = false;
    }
    update();
}
