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
#include <memory>

#include "common/types.h"
#include "dimensions.h"

template<typename TR>
struct RhombTraits
{
    virtual ~RhombTraits() = default;
    virtual TR get(uint8 ori, uint8 nmn) const = 0;
};

extern template struct RhombTraits<QRect>;
extern template struct RhombTraits<QBitmap>;
extern template struct RhombTraits<QPixmap>;

typedef std::shared_ptr<RhombTraits<QRect>> RhombDim;
typedef std::shared_ptr<RhombTraits<QBitmap>> RhombBmp;
typedef std::shared_ptr<RhombTraits<QPixmap>> RhombPix;

struct RhombSources;
struct SourceSizes;

class RhombLoader : public QObject
{
    Q_OBJECT
public:
    explicit RhombLoader(QObject *parent = 0);
    ~RhombLoader();
    bool load(const QPixmap& src);

signals:
    void loaded(const Vectors& vec, RhombDim dim, RhombBmp bmp, RhombPix pix);

private:
    Vectors m_vec;
    RhombDim m_dim;
    RhombBmp m_bmp;
    std::unique_ptr<RhombSources> m_src;
    std::unique_ptr<SourceSizes> m_ssz;
};

#endif // RHOMBLOADER_H
