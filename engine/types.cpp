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

#include "types.h"
#include <new>
#include <stdexcept>

template<typename T, size_t CS>
BList<T, CS>::BList(): m_count(0), m_gran(ITEM_NUM), m_level(0)
{
    m_bbr[0]=new Storage;
    m_back[0]=0;
}

template<typename T, size_t CS>
BList<T, CS>::~BList()
{
    _deleteTree(m_bbr[0], m_level);
}

template<typename T, size_t CS>
T& BList<T, CS>::at(size_t i)
{
    if (i >= m_count)
        throw std::out_of_range("BList::at");
    size_t gran = m_gran;
    size_t idx = i / gran;
    i %= gran;
    Storage* node = m_bbr[0];
    for (int k = 0; k < m_level; k++)
    {
        node = node->sub[idx];
        gran /= PTR_NUM;
        idx = i / gran;
        i %= gran;
    }
    return node->data[i];
}

template<typename T, size_t CS>
T* BList<T, CS>::push_back()
{
    size_t bk = m_back[m_level];
    if (bk < ITEM_NUM)
    {
        m_back[m_level]++;
        m_count++;
        return &m_bbr[m_level]->data[bk];
    }
    // Current chunk is full. Need to allocate new chunk
    // Find a chunk with free pointer
    int fl=-1;
    Storage* chain;
    for (int k = m_level - 1; k >= 0; k--)
    {
        if(m_back[k] < PTR_NUM)
        {
            fl = k;
            break;
        }
    }
    if (fl == -1)
    {
        //need to increase root level
        Storage* nr = new(std::nothrow) Storage;
        if(!nr)
            return nullptr;

        chain = _prepareChain(m_level+1);
        if(!chain)
        {
            delete nr;
            return nullptr;
        }
        nr->sub[0] = m_bbr[0];
        m_level++;
        m_gran *= PTR_NUM;
        m_bbr[0] = nr;
        m_back[0] = 1;
        fl=0;
    }
    else
    {
        chain = _prepareChain(m_level-fl);
        if(!chain) return nullptr;
    }
    Storage* ap = m_bbr[fl];
    ap->sub[m_back[fl]] = chain;
    Storage* cur = chain;
    m_back[fl]++;
    for (int k = fl + 1; k <= m_level; k++)
    {
        m_bbr[k]=cur;
        m_back[k]=1;
        if(k < m_level) cur = cur->sub[0];
    }
    m_count++;
    return &m_bbr[m_level]->data[0];
}

template<typename T, size_t CS>
typename BList<T, CS>::Storage* BList<T, CS>::_prepareChain(int n)
{
    Storage* root = nullptr;
    try
    {
        for(int i=0; i<n; i++)
        {
            Storage* cur = new Storage;
            cur->sub[0] = root;
            root = cur;
        }
    }
    catch(const std::bad_alloc&)
    {
        //Allocation failed. It is needed to decompose the already built chain
        while(root)
        {
            Storage* dd = root;
            root = root->sub[0];
            delete dd;
        }
        return nullptr;
    }
    return root;
}

template<typename T, size_t CS>
void BList<T, CS>::_deleteTree(Storage *root, int h)
{
    if(h)
        for(size_t i=0;i<PTR_NUM;i++)
        {
            _deleteTree(root->sub[i], h-1);
        }
    delete root;
}

template class BList<int32_t>;
template class BList<uint8_t>;

template class BList<innode>;
template class BList<ebrick>;
