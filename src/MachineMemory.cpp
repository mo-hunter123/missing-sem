#include "../include/MachineMemory.h"

void MachineMemory::collectMachineMemoryMetrics()
{

    this->current = pullMachineMemoryInformations();
    cout << "Free : " << this->current.freeMemory
         << "Avai : " << this->current.availableMemory
         << "Tot : " << this->current.totalMemory << endl;
}