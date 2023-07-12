#ifndef PROC_Service
#define PROC_Service

#include <fstream>

#define PROCDIR "/proc"
#define PROCMEMINFO PROCDIR "/meminfo"
#define PROCSMAPSROLLUP "/smaps_rollup"

#define MEMTOTAL_TOKEN "MemTotal:"
#define MEMAVAILABLE_TOKEN "MemAvailable:"
#define MEMFREE_TOKEN "MemFree:"
#define RSS_TOKEN "Rss:"

#define NO_MEM_MEASURE -1

typedef unsigned long long memory_t;
typedef int pid_t;

typedef struct machine_memory
{
    memory_t totalMemory;
    memory_t freeMemory;
    memory_t availableMemory;
};

memory_t pullMemoryUsageByPID(pid_t pid);
machine_memory pullMachineMemoryInformations();

#endif