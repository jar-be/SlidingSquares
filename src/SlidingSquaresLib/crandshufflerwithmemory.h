#ifndef CRANDSHUFFLERWITHMEMORY_H
#define CRANDSHUFFLERWITHMEMORY_H

#include "cshuffler.h"
#include "SlidingSquaresLib_global.h"

class SLIDINGSQUARESLIB_EXPORT CRandShufflerWithMemory : public CShuffler
{
public:
    size_t pick_move(const std::vector<size_t> &emptySquareNeighbours);
};

#endif // CRANDSHUFFLERWITHMEMORY_H
