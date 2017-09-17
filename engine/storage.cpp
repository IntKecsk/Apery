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

#include "storage.h"
#include <new>

template<typename T, size_t CS>
BList<T, CS>::BList(): m_count(0), m_level(0)
{
    m_bbr[0]=new uint8[CS];
    m_back[0]=0;
}

template<typename T, size_t CS>
BList<T, CS>::~BList()
{
    _deleteTree((void**)m_bbr[0], m_level);
}

template<typename T, size_t CS>
void* BList<T, CS>::_at(size_t i)
{
    if(i>=m_count) return nullptr;
    size_t idxs[m_level+1];
    idxs[0]=i%ITEM_NUM;
    i/=ITEM_NUM;
    for(int k=1; k<=m_level; k++)
    {
        idxs[k]=i%PTR_NUM;
        i/=PTR_NUM;
    }
    void** node = (void**)m_bbr[0];
    for(int k=0; k<m_level; k++)
    {
        node = (void**)node[idxs[m_level-k]];
    }
    return (uint8*)node + idxs[0]*IS;
}

template<typename T, size_t CS>
void* BList<T, CS>::push_back()
{
    size_t bk = m_back[m_level];
    if(bk<ITEM_NUM)
    {
        m_back[m_level]++;
        m_count++;
        return &m_bbr[m_level][bk*IS];
    }
    // Current chunk is full. Need to allocate new chunk
    // Find a chunk with free pointer
    int fl=-1;
    uint8* chain;
    for(int k=m_level-1; k>=0; k--)
    {
        if(m_back[k]<PTR_NUM)
        {
            fl = k;
            break;
        }
    }
    if(fl==-1)
    {
        //need to increase root level
        uint8* nr = new(std::nothrow) uint8[CS];
        if(!nr) return nullptr;
        chain = _prepareChain(m_level+1);
        if(!chain)
        {
            delete nr;
            return nullptr;
        }
        *(void**)nr = m_bbr[0];
        m_level++;
        m_bbr[0] = nr;
        m_back[0] = 1;
        fl=0;
    }
    else
    {
        chain = _prepareChain(m_level-fl);
        if(!chain) return nullptr;
    }
    void** ap = (void**)m_bbr[fl];
    ap[m_back[fl]] = chain;
    uint8* cur = chain;
    m_back[fl]++;
    for(int k=fl+1;k<=m_level;k++)
    {
        m_bbr[k]=cur;
        m_back[k]=1;
        if(k<m_level) cur=*(uint8**)cur;
    }
    m_count++;
    return m_bbr[m_level];
}

template<typename T, size_t CS>
uint8* BList<T, CS>::_prepareChain(int n)
{
    uint8* root = nullptr;
    try
    {
        for(int i=0; i<n; i++)
        {
            uint8* cur = new uint8[CS];
            *(void**)cur = root;
            root = cur;
        }
    }
    catch(std::bad_alloc)
    {
        //Allocation failed. It is needed to decompose the already built chain
        while(root)
        {
            uint8* dd = root;
            root=*(uint8**)root;
            delete dd;
            return nullptr;
        }
    }
    return root;
}

template<typename T, size_t CS>
void BList<T, CS>::_deleteTree(void** root, int h)
{
    if(h)
        for(size_t i=0;i<PTR_NUM;i++)
        {
            _deleteTree((void**)root[i], h-1);
        }
    delete root;
}

template class BList<int32>;
template class BList<uint8>;

template class BList<innode>;
template class BList<ebrick>;
