#ifndef CGAMESTATS_H
#define CGAMESTATS_H

#include "SlidingSquaresLib_global.h"
#include "cduration.h"

class SLIDINGSQUARESLIB_EXPORT CGameStats
{
    CDuration duration;
    int move_count;
public:
    CGameStats(int t_move_count, const CDuration t_duration);
    const CDuration &get_duration() const;
    int get_move_count() const;
};

#endif // CGAMESTATS_H
