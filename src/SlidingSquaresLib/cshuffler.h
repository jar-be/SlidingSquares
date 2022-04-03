#ifndef CSHUFFLER_H
#define CSHUFFLER_H

#include "csquare.h"
#include "SlidingSquaresLib_global.h"

#include <memory>
#include <vector>

/**
 * @brief The CShuffler base class. Used for shuffling the board
 */
class SLIDINGSQUARESLIB_EXPORT CShuffler
{
public:
    virtual ~CShuffler() {}
    /**
     * @brief pick_move Pick a move from the possible moves
     * @param emptySquareNeighbours possible moves
     * @return picked move
     */
    virtual size_t pick_move(const std::vector<size_t> &emptySquareNeighbours) =0;
};

#endif // CSHUFFLER_H
