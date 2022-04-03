#include "crandomshuffler.h"
#include <random>
#include <functional>
#include <chrono>
#include <memory>

CRandomShuffler::CRandomShuffler() : distribution()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator = std::make_unique<std::default_random_engine>(seed);
}

size_t CRandomShuffler::pick_move(const std::vector<size_t> &emptySquareNeighbours)
{
    auto dice = distribution(*generator);
    auto idx = dice % emptySquareNeighbours.size();
    return emptySquareNeighbours.at(idx);
}
