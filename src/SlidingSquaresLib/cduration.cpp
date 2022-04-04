#include "cduration.h"
#include "date/date.h"

#include <string>
#include <sstream>

long long CDuration::get_duration_in_seconds() const
{
    return duration.count();
}

std::string CDuration::get_formatted_duration() const
{
    std::ostringstream out;
    out << date::format("%T", duration);
    return out.str();
}
