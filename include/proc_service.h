#ifndef PROC_Service
#define PROC_Service

#include <fstream>
#include <sstream>
#include <list>
#include "types.h"
#include "CPUData.h"

using namespace std;

#define PROCDIR "/proc"
#define PROCMEMINFO PROCDIR "/meminfo"
#define UPTIME PROCDIR "/uptime"

#define PROCSMAPSROLLUP "/smaps_rollup"
#define PROCCMDLINE "/cmdline"
#define PROCSTAT "/stat"
#define PROCSTATDIR PROCDIR "/stat"

#define MEMTOTAL_TOKEN "MemTotal:"
#define MEMAVAILABLE_TOKEN "MemAvailable:"
#define MEMFREE_TOKEN "MemFree:"
#define RSS_TOKEN "Rss:"


#define PROC_STAT_INDEX 3
#define PROC_PPID_INDEX 4
#define PROC_UTIME_INDEX 14
#define PROC_STIME_INDEX 15 
#define PROC_THREADS_INDEX 20
#define PROC_STARTTIME_INDEX 22



// TODO: respect the unsigned long long type of the memory_t
#define NO_MEM_MEASURE 1


enum PULL_STATUS
{
    SUCCESS = 1,
    ERROR = -1
};


memory_t pullMemoryUsageByPID(pid_t pid, PULL_STATUS &status);
machine_memory pullMachineMemoryInformations();
std::list<pid_t> *getCurrentProcessesPIDs();
std::list<std::string> *execute_linux_command(const char *cmd);
std::string getProcessCmdLine(pid_t pid);
second_t getCPUUptime();
CPUData* pullProcStats();
CPUData* processCPUStat(string allCpusLine);


// the function can take ifstream or istringstream as parameters
process_stats getProcessStatFromFile(ifstream &stream);
process_stats getProcessStatFromFile(istringstream &stream);
process_stats getProcessStat(pid_t pid);

#endif
