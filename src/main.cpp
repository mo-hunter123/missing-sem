#include <iostream>
#include "MachineMemory.h"

using namespace std;

int main(int argc, char const *argv[])
{
    MachineMemory *machineMemory = new MachineMemory();
    machineMemory->collectMachineMemoryMetrics();
    return 0;
}
