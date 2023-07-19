#include "Process.h"

Process::Process(memory_t memoryUsage, pid_t pid)
{
    this->memoryUsage = memoryUsage;
    this->pid = pid;
}

pid_t Process::getPid()
{
    return this->pid;
}

string Process::toString()
{
    return string("PID :") + to_string(this->pid) + string(" | Memory usage : ") + to_string(this->memoryUsage);
}

memory_t Process::getMemoryUsage()
{
    return this->memoryUsage;
}

pid_t Process::getPID()
{
    return this->pid;
}