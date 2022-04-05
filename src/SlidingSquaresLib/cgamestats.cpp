#include "cgamestats.h"

const CDuration &CGameStats::get_duration() const
{
    return duration;
}

int CGameStats::get_move_count() const
{
    return move_count;
}

CGameStats::CGameStats(int t_move_count, const CDuration t_duration)
    : duration(t_duration), move_count(t_move_count)
{
}
