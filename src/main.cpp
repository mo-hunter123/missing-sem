#include <iostream>
#include "../include/MachineMemory.h"
#include "../include/Process.h"

using namespace std;

int main(int argc, char const *argv[])
{
    MachineMemory *machineMemory = new MachineMemory();
    machineMemory->collectMachineMemoryMetrics();

    pid_t pid = 3225;
    memory_t me = pullMemoryUsageByPID(pid);

    Process *process = new Process(me, pid);
    cout << "Mem: " << process->toString() << endl;

    return 0;
}
