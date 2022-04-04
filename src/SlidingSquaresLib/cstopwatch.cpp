#include "cstopwatch.h"
namespace cr = std::chrono;

CStopwatch::CStopwatch()
    : started(false)
{
    auto now = cr::system_clock::now();
    start_time = now;
    stop_time = now;
}

void CStopwatch::start()
{
    started = true;
    start_time = cr::system_clock::now();
}

void CStopwatch::stop()
{
    started = false;
    stop_time = cr::system_clock::now();
}

CDuration CStopwatch::get_duration() const
{
    return CDuration(get_chrono_duration());
}

cr::duration<long> CStopwatch::get_chrono_duration() const
{
    auto end = stop_time;
    if (started) {
        end = cr::system_clock::now();
    }
    auto time_taken = end - start_time;
    auto in_seconds = cr::duration_cast<cr::seconds>(time_taken);
    return in_seconds;
}
