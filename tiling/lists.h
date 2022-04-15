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

#ifndef APERY_LISTS_H
#define APERY_LISTS_H

#include <cstddef>

#include "types.h"
#include "quadtree.h"

using std::size_t;

template<typename T, size_t CS = 8192>
class BList
{
public:
    BList();
    ~BList();
    size_t size() const {return m_count;}
    T& at(size_t i);
    const T& at(size_t i) const {return const_cast<BList*>(this)->at(i); }
    T* push_back();
    bool push_back(T it) {
        T* st = push_back();
        if(st)
        {
            *st = it;
            return true;
        }
        else
            return false;
    }
private:
    static constexpr size_t IS = sizeof(T);
    static constexpr size_t ITEM_NUM = CS / IS;
    static_assert(ITEM_NUM, "Chunk size too small");
    static constexpr size_t PTR_NUM = CS / sizeof(void*);
    static_assert(PTR_NUM, "Chunk size too small");
    static_assert(PTR_NUM > 1, "Chunk size too small (singularity)");
    static constexpr int LEVEL_BND = 8;

    union Storage
    {
        T data[ITEM_NUM];
        Storage* sub[PTR_NUM];
    };

    size_t m_count;
    size_t m_gran; // TODO: implement!
    int m_level;
    Storage* m_bbr[LEVEL_BND];
    size_t m_back[LEVEL_BND];
    Storage* _prepareChain(int n);
    void _deleteTree(Storage* root, int h);
};

extern template class BList<int32_t>;
extern template class BList<uint8_t>;
extern template class BList<innode>;
extern template class BList<ebrick>;

template<typename T, size_t CS = 8192>
class Bilist
{
public:
    T& at(ptrdiff_t i)
    {
        if (i >= 0)
            return ge0.at(i);
        else
            return lt0.at(~i);
    }

    const T& at(ptrdiff_t i) const
    {
        return const_cast<Bilist*>(this)->at(i);
    }

    T* push_back()
    {
        return ge0.push_back();
    }

    bool push_back(T it)
    {
        return ge0.push_back(it);
    }

    T* push_front()
    {
        return lt0.push_back();
    }

    bool push_front(T it)
    {
        return lt0.push_back(it);
    }

    ptrdiff_t ubound() const
    {
        return ge0.size();
    }

    ptrdiff_t lbound() const
    {
        return ~lt0.size();
    }

private:
    BList<T, CS> ge0;
    BList<T, CS> lt0;
};

#endif // ENGINE_TYPES_H
