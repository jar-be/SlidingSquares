#ifndef CRANDOMSHUFFLER_H
#define CRANDOMSHUFFLER_H

#include "cshuffler.h"
#include "SlidingSquaresLib_global.h"
#include <random>
#include <functional>
#include <memory>

/**
 * @brief The CRandomShuffler class. Shuffles board randomly picking a square to move
 */
class SLIDINGSQUARESLIB_EXPORT CRandomShuffler : public CShuffler
{
    std::unique_ptr<std::default_random_engine> generator;
    std::uniform_int_distribution<int> distribution;
public:
    CRandomShuffler();
    size_t pick_move(const std::vector<size_t> &emptySquareNeighbours);
};

#endif // CRANDOMSHUFFLER_H
