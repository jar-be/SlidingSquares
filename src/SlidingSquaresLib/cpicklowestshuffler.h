#ifndef CPICKLOWESTSHUFFLER_H
#define CPICKLOWESTSHUFFLER_H

#include "cshuffler.h"

class CPickLowestShuffler : public CShuffler
{
    bool has_previous_pick;
    size_t previous_pick;
public:
    CPickLowestShuffler();
    size_t pick_move(const std::vector<size_t> &emptySquareNeighbours);
};

#endif // CPICKLOWESTSHUFFLER_H
