
#include <iostream>
#include <fstream>
#include <string.h>
#include "proc_service.h"

using namespace std;

class MachineMemory
{
private:
    machine_memory current;

public:
    void collectMachineMemoryMetrics();
};