#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "include/doctest.h"
#include "../include/utils.h"

TEST_CASE("should give seconds in format x days, HH:MM:SS")
{
    // given
    string expected = "1 days, 00:00:00";
    unsigned int seconds = 86400;

    // when
    string result = convertSecondsToVisibleDuration(seconds);

    // then
    CHECK(expected == result);
}
