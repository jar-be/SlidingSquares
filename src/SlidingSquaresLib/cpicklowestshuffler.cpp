#include "cpicklowestshuffler.h"
#include <algorithm>

CPickLowestShuffler::CPickLowestShuffler() : has_previous_pick(false), previous_pick(0)
{

}

size_t CPickLowestShuffler::pick_move(const std::vector<size_t> &emptySquareNeighbours)
{
    auto neighbours = std::vector<size_t>(emptySquareNeighbours);
    if (has_previous_pick) {
        auto previous = std::find(neighbours.begin(), neighbours.end(), previous_pick);
        if (previous != neighbours.end()) {
            neighbours.erase(previous);
        }
    }

    size_t chosen = *std::min_element(neighbours.begin(), neighbours.end());
    previous_pick = chosen;
    has_previous_pick = true;
    return chosen;
}
