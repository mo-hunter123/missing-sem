#include "../include/Machine.h"

Machine::Machine()
{
    this->machineMemory = new MachineMemory();
    this->machineProcesses = new MachineProcesses();
}

void Machine::init()
{
    this->machineMemory->collectMachineMemoryMetrics();
    this->machineProcesses->constructProcessList();
}

MachineMemory *Machine::getMachineMemory()
{
    return this->machineMemory;
}

MachineProcesses *Machine::getMachineProcesses()
{
    return this->machineProcesses;
}