#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "include/doctest.h"
#include "../include/utils.h"
#include "../include/proc_service.h"
#include "../include/MachineProcesses.h"

// we will accept that getCurrentProcessesPIDs() is true and delivers
// all current PIDs correctly

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


TEST_CASE("process hashtable should contains the same number of current PIDs")
{
    // given
    std::list<pid_t> *pid_list = getCurrentProcessesPIDs();
    MachineProcesses *machineProcesses = new MachineProcesses();

    int expectedPIDsCount = pid_list->size();

    // when
    machineProcesses->constructProcessList();
    int actualPIDsCount = machineProcesses->getProcessList()->size();

    // then
    CHECK(expectedPIDsCount == actualPIDsCount);
}

TEST_CASE("should get the process stats ppid, state, num_threads") {

    // given
    // this is a copy of the /proc/[pid]/stat result 
    string str = "1099943 (chrome) S 1099883 2930 2930 0 -1 1077936128 3226412 0 311 0 17964 9707 0 0 20 0 9 0 9891614 34751942656 23978 18446744073709551615 94342536601600 94342707773696 140724999732128 0 0 0 0 4098 25167100 0 0 0 17 1 0 0 0 0 0 94342716784640 94342717342728 94342736535552 140724999735018 140724999735347 140724999735347 140724999737321 0"; 

    std::istringstream iss(str);

    // when
    process_stats processStat = getProcessStatFromFile(iss);

    // then
    CHECK(processStat.ppid == 1099883);
    CHECK(processStat.state == 'S');
    CHECK(processStat.num_threads == 9);
    CHECK(processStat.utime == 17964);
    CHECK(processStat.stime == 9707);
    CHECK(processStat.starttime == 9891614);
}
