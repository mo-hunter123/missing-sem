#include "Process.h"

Process::Process(memory_t memoryUsage,
                 pid_t pid,
                 string cmdLine,
                 char state,
                 pid_t ppid,
                 int num_threads,
                 second_t elapsed_sec,
                 float process_usage)
{
    this->memoryUsage = memoryUsage;
    this->pid = pid;
    this->cmdline = cmdLine;
    this->state = state;
    this->ppid = ppid;
    this->num_threads = num_threads;
    this->elapsed_sec = elapsed_sec;
    this->process_usage = process_usage;
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

string Process::getCmdLine()
{
    return this->cmdline;
}

char Process::getState()
{
    return this->state;
}

pid_t Process::getPpid()
{
    return this->ppid;
}

int Process::getNumThreads()
{
    return this->num_threads;
}

second_t Process::getElapsedSec()
{
    return this->elapsed_sec;
}

float Process::getUsagePercentage()
{
    return this->process_usage;
}
