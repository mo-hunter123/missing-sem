#ifndef UTILS_H
#define UTILS_H 

#include <string>
#include "types.h"

using namespace std;

#define DAY_TO_HOURS 24
#define DAY_TO_MINUTES 1440
#define DAY_TO_SECONDS 86400

#define HOURS_TO_SECONDS 3600
#define MINUTES_TO_SECONDS 60

string convertSecondsToVisibleDuration(second_t seconds);
second_t convertClockTicksToSeconds(clktck_t clk_tck);

#endif