#ifndef CRANDSHUFFLERWITHMEMORY_H
#define CRANDSHUFFLERWITHMEMORY_H

#include "cshuffler.h"
#include "SlidingSquaresLib_global.h"

class SLIDINGSQUARESLIB_EXPORT CRandShufflerWithMemory : public CShuffler
{
public:
    void Shuffle(std::vector<std::unique_ptr<CSquare> > &boardState);
};

#endif // CRANDSHUFFLERWITHMEMORY_H
