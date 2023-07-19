#ifndef PROCESS_H
#define PROCESS_H

#include "proc_service.h"

using namespace std;

class Process
{

private:
    memory_t memoryUsage;
    pid_t pid;

public:
    Process(memory_t memoryUsage, pid_t pid);
    pid_t getPid();
    memory_t getMemoryUsage();
    pid_t getPID();
    string toString();
};

#endif