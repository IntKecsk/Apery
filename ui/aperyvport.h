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

#ifndef APERYWGT_H
#define APERYWGT_H

#include <QWidget>
//#include <QOpenGLWidget>
//#include <QOpenGLFunctions>
#include "common/types.h"
#include "engine/universe.h"

class CellDrawer;
class RhombPixmaps;

class AperyVPort : public QWidget //QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    AperyVPort(QWidget *parent = 0);
    void loadImage(const QString& file);
    ~AperyVPort();
protected:
    //virtual void initializeGL() override;
    //virtual void resizeGL(int w, int h) override;
    //virtual void paintGL() override;
    virtual void paintEvent(QPaintEvent *e) override;
    virtual void mousePressEvent(QMouseEvent *e) override;
    virtual void mouseMoveEvent(QMouseEvent *e) override;
    virtual void mouseReleaseEvent(QMouseEvent *e) override;
private:
    RhombPixmaps* m_rpx;
    Universe* m_univ;

    int ox, oy; //Origin coords
    int dwx, dnx, dwy, dny; //WN-coordinates of the cell in the origin
    void drawCellRC(CellDrawer &cd, quint8 ci, WN x, WN y);

    bool m_drag;
    int drag_start_x, drag_start_y, orig_ox, orig_oy;
};

#endif // APERYWGT_H
