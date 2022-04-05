#ifndef CDURATION_H
#define CDURATION_H

#include "SlidingSquaresLib_global.h"

#include <chrono>
#include <string>

class SLIDINGSQUARESLIB_EXPORT CDuration
{
    std::chrono::duration<long> duration;
public:
    CDuration(const std::chrono::duration<long> &t_duration) : duration(t_duration) {};
    long long get_duration_in_seconds() const;
    std::string get_formatted_duration() const;
};

#endif // CDURATION_H
