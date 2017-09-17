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

#ifndef STORAGE_H
#define STORAGE_H

#include <cstddef>

#include "common/types.h"
#include "quadtree.h"

using std::size_t;

template<typename T, size_t CS=8192>
class BList
{
public:
    BList();
    ~BList();
    size_t count() const {return m_count;}
    void* _at(size_t i);
    const void* _at(size_t i) const {return const_cast<BList*>(this)->_at(i); }
    T& at(size_t i) {return *(T*)_at(i); }
    const T& at(size_t i) const {return *(const T*)_at(i); }
    void* push_back();
    bool push_back(T it) {
        T* st = (T*)push_back();
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
    size_t m_count;
    int m_level;
    static constexpr int LEVEL_BND = 8;
    uint8* m_bbr[LEVEL_BND];
    size_t m_back[LEVEL_BND];
    uint8* _prepareChain(int n);
    void _deleteTree(void** root, int h);
};

extern template class BList<int32>;
extern template class BList<uint8>;
extern template class BList<innode>;
extern template class BList<ebrick>;

#endif // STORAGE_H
