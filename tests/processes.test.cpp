
#include "include/doctest.h"
#include "../include/utils.h"
#include "../include/proc_service.h"
#include "../include/MachineProcesses.h"
#include "../include/CPUData.h"

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
    try
    {
        std::list<pid_t> *pid_list = getCurrentProcessesPIDs();
        MachineProcesses *machineProcesses = new MachineProcesses();

        int expectedPIDsCount = pid_list->size();

        // when
        machineProcesses->constructProcessList();
        int actualPIDsCount = machineProcesses->getProcessList()->size();

        // then
        WARN(expectedPIDsCount == actualPIDsCount);
    }
    catch (...)
    {
        cout << "Problem while reading the PIDs" << endl;
    }
}

TEST_CASE("should get the process stats ppid, state, num_threads")
{
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

TEST_CASE("should read the cpu data stat")
{
    // given
    // cpu user nice system idle iowait irq softirq steal
    // this is a line example from /proc/stat
    string proc_stat_str = "cpu  42095052 181507 9147736 21864381 162987 0 116668 0 0 0";

    // when
    CPUData *cpuData = processCPUStat(proc_stat_str);

    // then
    CHECK(cpuData->getUserTime() == 42095052);
    CHECK(cpuData->getNiceTime() == 181507);
    CHECK(cpuData->getSystemTime() == 9147736);
    CHECK(cpuData->getIdleTime() == 21864381);
    CHECK(cpuData->getIowaitTime() == 162987);
    CHECK(cpuData->getIrq() == 0);
    CHECK(cpuData->getSoftirq() == 116668);
    CHECK(cpuData->getStealTime() == 0);
}

TEST_CASE("should have the same time as uptime ")
{
    // given
    // cpu user nice system idle iowait irq softirq steal
    // this is a line example from /proc/stat
    string proc_stat_str = "cpu  42095052 181507 9147736 21864381 162987 0 116668 0 0 0";

    // when
    CPUData *cpuData = pullProcStats();
    second_t uptime = getCPUUptime();

    second_t uptime_stat = convertClockTicksToSeconds(cpuData->getTotalTime());

    // then
    cout << "DATA: " << convertSecondsToVisibleDuration(uptime_stat) << " | " << convertSecondsToVisibleDuration(uptime) << endl;
    WARN(uptime_stat == uptime);
}
