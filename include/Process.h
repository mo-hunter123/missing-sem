#ifndef PROCESS_H
#define PROCESS_H

#include "proc_service.h"

using namespace std;

class Process
{

private:
    memory_t memoryUsage;
    pid_t pid;
    string cmdline;

public:
    Process(memory_t memoryUsage, pid_t pid, string cmdLine);
    pid_t getPid();
    memory_t getMemoryUsage();
    pid_t getPID();
    string getCmdLine();
    string toString();
};

#endif