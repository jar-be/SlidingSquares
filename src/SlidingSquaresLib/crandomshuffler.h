#ifndef CRANDOMSHUFFLER_H
#define CRANDOMSHUFFLER_H

#include "cshuffler.h"
#include "SlidingSquaresLib_global.h"

class SLIDINGSQUARESLIB_EXPORT CRandomShuffler : public CShuffler
{
public:
    void Shuffle(std::vector<std::unique_ptr<CSquare> > &boardState);
};

#endif // CRANDOMSHUFFLER_H
