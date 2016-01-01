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
#include "aperyvport.h"
#include "ptdefs.h"
#include "celldrawer.h"
#include "rhombpixmaps.h"

#include <QDebug>
#include <QFile>

AperyVPort::AperyVPort(QWidget *parent)
    : QWidget(parent),  //QOpenGLWidget(parent)
      ox(400), oy(400), dwx(0), dnx(0), dwy(0), dny(0), m_drag(false)
{
    m_rpx = new RhombPixmaps(this);
    m_univ = new Universe(4, 0, 0, 2);
    if(!m_univ->isValid())
        return;
    for(int i=-21; i<21; i+=3)
        for(int j=-21; j<21; j+=3)
            m_univ->resolveCell(i, j);
}

void AperyVPort::loadImage(const QString &file)
{
    QPixmap px(file);
    m_rpx->loadPixmaps(px);
}

AperyVPort::~AperyVPort()
{
    delete m_univ;
}

/*void AperyVPort::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void AperyVPort::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void AperyVPort::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
}*/

void AperyVPort::drawCellRC(CellDrawer& cd, quint8 ci, WN x, WN y)
{
    qint32 wx=x.w-dwx;
    qint32 nx=x.n-dnx;
    qint32 wy=y.w-dwy;
    qint32 ny=y.n-dny;
    cd.drawCell(ci, wx*XWX+nx*XNX+wy*YWX+ny*YNX, wx*XWY+nx*XNY+wy*YWY+ny*YNY);
}

void AperyVPort::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    if(!m_univ->isValid() || !m_rpx->loaded())
        return;
    CellDrawer cd(m_rpx, this);
    cd.translate(ox, oy);
    //cd.scale(8, 8);
    Range rx = m_univ->rangeX();
    //qDebug() << rx.b << rx.e;
    Range ry = m_univ->rangeY();
    for(int x=rx.b; x<rx.e; x++)
    {
        WN wnx = m_univ->wnX(x);
        for(int y=ry.b; y<ry.e; y++)
        {
            WN wny = m_univ->wnY(y);
            quint8 ci = m_univ->at(x, y);
            if(ci)
            {
                drawCellRC(cd, ci, wnx, wny);
            }
        }
    }
}

void AperyVPort::mousePressEvent(QMouseEvent *e)
{
    if(e->button()!=Qt::LeftButton) return e->ignore();
    m_drag = true;
    drag_start_x = e->x();
    drag_start_y = e->y();
    orig_ox = ox;
    orig_oy = oy;
}

void AperyVPort::mouseMoveEvent(QMouseEvent *e)
{
    if(!(m_drag && (e->buttons()&Qt::LeftButton))) return e->ignore();
    ox = orig_ox + (e->x()-drag_start_x);
    oy = orig_oy + (e->y()-drag_start_y);
    update();
}

void AperyVPort::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button()!=Qt::LeftButton) return e->ignore();
    ox = orig_ox + (e->x()-drag_start_x);
    oy = orig_oy + (e->y()-drag_start_y);
    m_drag = false;
    update();
}
