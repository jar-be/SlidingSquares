#ifndef CSTOPWATCH_H
#define CSTOPWATCH_H

#include "cduration.h"

#include <chrono>

class CStopwatch
{
    bool started;
    std::chrono::system_clock::time_point start_time;
    std::chrono::system_clock::time_point stop_time;
public:
    CStopwatch();;
    bool isStarted() const { return started; }
    void start();
    void stop();
    CDuration get_duration() const;
private:
    std::chrono::duration<long> get_chrono_duration() const;
};

#endif // CSTOPWATCH_H
