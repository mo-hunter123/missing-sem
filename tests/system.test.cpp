
#include <iostream>
#include <cmath>
#include "include/doctest.h"
#include "../include/CPUData.h"
#include "../include/MachineProcesses.h"


using namespace std;

TEST_CASE("should clone the CPUData object after deletion")
{
    CPUData *toBeCloned = new CPUData(42095052, 181507, 9147736, 21864381, 162987, 0, 116668, 0);

    CPUData *clone = new CPUData(*toBeCloned);

    delete toBeCloned;

    CHECK(clone->getUserTime() == 42095052);
    CHECK(clone->getNiceTime() == 181507);
    CHECK(clone->getSystemTime() == 9147736);
}

TEST_CASE("should return the correct cpu usage")
{
    // from t1 to t2 we recorded the following :
    //  - last_cpu      at t1
    //  - current_cpu   at t2

    // given
    CPUData *last_cpu = new CPUData(13, 0, 0, 7, 0, 0, 0, 0);
    CPUData *current_cpu = new CPUData(41, 0, 0, 9, 0, 0, 0, 0);

    // when
    MachineProcesses *test_machine = new MachineProcesses(current_cpu, last_cpu, NULL);

    // then
    CHECK(round(test_machine->getCpuUsage()) == 93);
}
