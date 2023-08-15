#include "../include/MachineMemory.h"
#include "../include/proc_service.h"

void MachineMemory::collectMachineMemoryMetrics()
{

    this->current = pullMachineMemoryInformations();
    cout << "Free : " << this->current.freeMemory
         << "Avai : " << this->current.availableMemory
         << "Tot : " << this->current.totalMemory << endl;
}

machine_memory MachineMemory::getCurrentMemory()
{
    return this->current;
}

void MachineMemory::updateMemoryStatistics() {
    this->current = pullMachineMemoryInformations();
}