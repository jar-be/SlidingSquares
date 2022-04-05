#ifndef CRANDSHUFFLERWITHMEMORY_H
#define CRANDSHUFFLERWITHMEMORY_H

#include "cshuffler.h"
#include "SlidingSquaresLib_global.h"
#include "crandomshuffler.h"

#include <random>
#include <functional>
#include <memory>
#include <deque>

/**
 * @brief The CRandShufflerWithMemory class. Shuffles the board randomly but not
 * using the previous moves.
 */
class SLIDINGSQUARESLIB_EXPORT CRandShufflerWithMemory : public CRandomShuffler
{
    bool has_previous_pick;
    size_t previous_pick;
public:
    CRandShufflerWithMemory();
    size_t pick_move(const std::vector<size_t> &emptySquareNeighbours);
};

#endif // CRANDSHUFFLERWITHMEMORY_H
