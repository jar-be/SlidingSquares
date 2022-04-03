#include "crandshufflerwithmemory.h"

#include <chrono>
#include <algorithm>
#include <functional>
#include <iostream>

CRandShufflerWithMemory::CRandShufflerWithMemory() : distribution()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator = std::make_unique<std::default_random_engine>(seed);
}


size_t CRandShufflerWithMemory::pick_move(const std::vector<size_t> &emptySquareNeighbours)
{
    if (previous_picks.size() > memory_depth) {
        previous_picks.pop_back();
    }
    auto dice = std::bind (distribution, *generator);
    auto diceRoll = dice() % emptySquareNeighbours.size();
    auto idx = emptySquareNeighbours.at(diceRoll);
    while (std::any_of(previous_picks.begin(), previous_picks.end(),
                       [&idx](auto pick) { return pick == idx; })) {
        diceRoll = dice() % emptySquareNeighbours.size();
        idx = emptySquareNeighbours.at(diceRoll);
        std::cout << "Dice roll: " << diceRoll << ", idx: " << idx << std::endl;
    }
    previous_picks.push_front(idx);
    return idx;
}
