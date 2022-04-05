#include "crandshufflerwithmemory.h"

#include <chrono>
#include <algorithm>
#include <functional>
#include <iostream>

CRandShufflerWithMemory::CRandShufflerWithMemory() : CRandomShuffler(), has_previous_pick(false)
{
}


size_t CRandShufflerWithMemory::pick_move(const std::vector<size_t> &emptySquareNeighbours)
{
    auto idx = CRandomShuffler::pick_move(emptySquareNeighbours);
    if (has_previous_pick) {
        while (idx == previous_pick) {
            idx = CRandomShuffler::pick_move(emptySquareNeighbours);
        }
    } else {
        has_previous_pick = true;
        previous_pick = idx;
    }
    return idx;
}
