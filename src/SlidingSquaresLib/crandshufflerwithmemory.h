#ifndef CRANDSHUFFLERWITHMEMORY_H
#define CRANDSHUFFLERWITHMEMORY_H

#include "cshuffler.h"
#include "SlidingSquaresLib_global.h"

#include <random>
#include <functional>
#include <memory>
#include <deque>

/**
 * @brief The CRandShufflerWithMemory class. Shuffles the board randomly but not
 * using the previous moves.
 */
class SLIDINGSQUARESLIB_EXPORT CRandShufflerWithMemory : public CShuffler
{
    static constexpr int memory_depth = 5;
    std::unique_ptr<std::default_random_engine> generator;
    std::uniform_int_distribution<int> distribution;
    std::deque<size_t> previous_picks;
public:
    CRandShufflerWithMemory();
    size_t pick_move(const std::vector<size_t> &emptySquareNeighbours);
};

#endif // CRANDSHUFFLERWITHMEMORY_H
