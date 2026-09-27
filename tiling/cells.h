//
// Created by IntKecsk on 03.04.2024.
//

#ifndef APERY_CELLS_H
#define APERY_CELLS_H

#include "defs.h"

struct CellSize {
    uint8_t width_x;
    uint8_t width_y;
};

inline constexpr Cell::ArcheArray<CellSize> cell_arche{{
    {0, 0}, //N
    {1, 1}, //W
    {1, 1}, //V
    {1, 1}, //O
    {1, 0}, //S
    {1, 0}, //F
    {1, 0}, //B
    {1, 1}  //Q
}};

#endif //APERY_CELLS_H
