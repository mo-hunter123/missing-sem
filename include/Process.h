#ifndef PROCESS_H
#define PROCESS_H

#include "types.h"

using namespace std;

class Process
{

private:
    memory_t memoryUsage;
    pid_t pid;
    string cmdline;
    char state;
    pid_t ppid;
    int num_threads;
    second_t elapsed_sec;
    float process_usage; // persentage

public:
    Process(memory_t memoryUsage,
            pid_t pid,
            string cmdLine,
            char state,
            pid_t ppid,
            int num_threads,
            second_t elapsed_sec,
            float process_usage);

    pid_t getPid();
    memory_t getMemoryUsage();
    pid_t getPID();
    string getCmdLine();
    char getState();
    pid_t getPpid();
    second_t getElapsedSec();
    float getUsagePercentage();
    int getNumThreads();
    string toString();
};

#endif
