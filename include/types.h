#ifndef MI_TYPES
#define MI_TYPES

#include <string>

typedef unsigned long long memory_t;
typedef int pid_t;
typedef unsigned int second_t;
typedef unsigned long int clktck_t;

typedef struct machine_memory
{
    memory_t totalMemory;
    memory_t freeMemory;
    memory_t availableMemory;
};

typedef struct process_stats
{
    char state; // 3
    pid_t ppid; // 4

    // following times are in clock ticks ==> divide by sysconf(_SC_CLK_TCK)
    // to get seconds
    unsigned long long int utime;     // 14
    unsigned long long int stime;     // 15
    unsigned long long int starttime; // 22

    int num_threads; // 20
};

#endif