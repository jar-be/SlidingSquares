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
    virtual void Shuffle(std::vector<std::unique_ptr<CSquare>> &boardState) =0;
};

#endif // CSHUFFLER_H
