#include "utils.h"
#include "proc_service.h"
#include <iomanip>
#include <sstream>
#include <unistd.h>

string convertSecondsToVisibleDuration(second_t seconds)
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

second_t convertClockTicksToSeconds(clktck_t clk_tck)
{
    return clk_tck / sysconf(_SC_CLK_TCK);
}
