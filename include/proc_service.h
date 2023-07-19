#ifndef PROC_Service
#define PROC_Service

#include <fstream>
#include <list>

#define PROCDIR "/proc"
#define PROCMEMINFO PROCDIR "/meminfo"
#define UPTIME PROCDIR "/uptime"

#define PROCSMAPSROLLUP "/smaps_rollup"
#define PROCCMDLINE "/cmdline"


#define MEMTOTAL_TOKEN "MemTotal:"
#define MEMAVAILABLE_TOKEN "MemAvailable:"
#define MEMFREE_TOKEN "MemFree:"
#define RSS_TOKEN "Rss:"

// TODO: respect the unsigned long long type of the memory_t
#define NO_MEM_MEASURE 1

typedef unsigned long long memory_t;
typedef int pid_t;
typedef unsigned int second_t;

enum PULL_STATUS
{
    SUCCESS = 1,
    ERROR = -1
};

typedef struct machine_memory
{
    memory_t totalMemory;
    memory_t freeMemory;
    memory_t availableMemory;
};

memory_t pullMemoryUsageByPID(pid_t pid, PULL_STATUS& status);
machine_memory pullMachineMemoryInformations();
std::list<pid_t> *getCurrentProcessesPIDs();
std::list<std::string> *execute_linux_command(const char *cmd);
std::string getProcessCmdLine(pid_t pid);
second_t getCPUUptime();


#endif