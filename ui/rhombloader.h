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

#ifndef RHOMBLOADER_H
#define RHOMBLOADER_H

#include <QObject>
#include <QImage>
#include <memory>

#include "tiling/cells.h"
#include "dimensions.h"

struct RhombDim
{
    explicit RhombDim(const Vectors& vec);
    const QRect& get(Tile t) const;

    QRect m_wide[10];
    QRect m_narrow[10];
};

template<typename TImg>
struct RhombMask
{
    const TImg& get(Tile t) const;

    TImg m_wide[5];
    TImg m_narrow[5];
};
extern template struct RhombMask<QImage>;

struct RhombPix
{
    virtual ~RhombPix() = default;
    virtual const QPixmap& get(int state, Tile t) const = 0;
    virtual int nstates() const = 0;
};

typedef std::shared_ptr<RhombDim> RhombDimSP;
typedef std::shared_ptr<RhombMask<QImage>> RhombMaskSP;
typedef std::shared_ptr<RhombPix> RhombPixSP;

class RhombLoader : public QObject
{
    Q_OBJECT
public:
    explicit RhombLoader(QObject *parent = nullptr);
    ~RhombLoader();
    bool load(const QPixmap& src, int nstates);
    QImage dump(bool nmn);

signals:
    void loaded(const Vectors& vec, RhombDimSP dim, RhombMaskSP mask, RhombPixSP pix);

private:
    struct Impl;

    template<template<typename> typename TData>
    bool doLoad(const QPixmap& src, const QSize& ssz, int nstates, bool dup);
    template<template<typename> typename TData>
    QImage doDump(const QSize& ssz);

    Vectors m_vec;
    RhombDimSP m_dim;
    RhombMaskSP m_mask;
    RhombPixSP m_pix;
    std::unique_ptr<Impl> m_i;
};

#endif // RHOMBLOADER_H
