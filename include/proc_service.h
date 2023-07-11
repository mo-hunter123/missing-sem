#ifndef PROC_Service
#define PROC_Service

#define PROCDIR "/proc"
#define PROCMEMINFO PROCDIR "/meminfo"
#define MEMTOTAL_TOKEN "MemTotal:"
#define MEMAVAILABLE_TOKEN "MemAvailable:"
#define MEMFREE_TOKEN "MemFree:"

typedef unsigned long long memory_t;

typedef struct machine_memory
{
    memory_t totalMemory;
    memory_t freeMemory;
    memory_t availableMemory;
};

memory_t pullMemoryUsageByPID(int pid);
machine_memory pullMachineMemoryInformations();

#endif