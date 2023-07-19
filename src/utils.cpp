#include "utils.h"
#include <iomanip>
#include <sstream>


string convertSecondsToVisibleDuration(unsigned int seconds)
{
    std::ostringstream resultStream;

    unsigned int days = seconds / DAY_TO_SECONDS;
    seconds %= DAY_TO_SECONDS;
    if (days > 0)
        resultStream << days << " days, ";

    unsigned int hours = seconds / HOURS_TO_SECONDS;
    seconds %= HOURS_TO_SECONDS;
    resultStream << std::setfill('0') << std::setw(2) << hours << ":";

    unsigned int minutes = seconds / MINUTES_TO_SECONDS;
    seconds %= MINUTES_TO_SECONDS;
    resultStream << std::setfill('0') << std::setw(2) << minutes << ":";

    resultStream << std::setfill('0') << std::setw(2) << seconds;

    return resultStream.str();
}
