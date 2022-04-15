#ifndef APERY_TEMPLATES_H
#define APERY_TEMPLATES_H

#include "cells.h"

struct CellArcheBase
{
    uint8_t num; ///< Number of tiles in the cell;
    uint8_t width_x; ///< X width descriptor
    uint8_t width_y; ///< Y width descriptor
};

constexpr std::array<CellArcheBase, Cell::NUM_ARCHETYPES> cell_def_arche_base = {{ 
    {9, 2, 2}, //N
    {9, 3, 3}, //W
    {8, 3, 3}, //V
    {8, 3, 3}, //O
    {9, 3, 2}, //S
    {7, 3, 2}, //F
    {7, 3, 2}, //B
    {8, 3, 3}  //Q
}};

#endif
