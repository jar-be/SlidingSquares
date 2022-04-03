#ifndef CSHUFFLER_H
#define CSHUFFLER_H

#include "csquare.h"
#include "SlidingSquaresLib_global.h"

#include <memory>
#include <vector>

class SLIDINGSQUARESLIB_EXPORT CShuffler
{
public:
    virtual ~CShuffler() {}
    virtual size_t pick_move(const std::vector<size_t> &emptySquareNeighbours) =0;
};

#endif // CSHUFFLER_H
