
#ifndef MACHINE_MEMORY_H
#define MACHINE_MEMORY_H

#include <iostream>
#include <fstream>
#include <string.h>
#include "types.h"

using namespace std;

class MachineMemory
{
private:
    machine_memory current;

public:
    void collectMachineMemoryMetrics();
    machine_memory getCurrentMemory();
    void updateMemoryStatistics();
};

#endif