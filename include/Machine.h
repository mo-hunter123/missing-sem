
#include "MachineProcesses.h"
#include "MachineMemory.h"

class Machine
{
private:
    MachineMemory *machineMemory;
    MachineProcesses *machineProcesses;

public:
    Machine();
    void init();
    MachineMemory* getMachineMemory();
    MachineProcesses* getMachineProcesses();
};
