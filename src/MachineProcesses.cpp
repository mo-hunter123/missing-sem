#include "MachineProcesses.h"
#include <iomanip>
#include <unistd.h>
#include "utils.h"

MachineProcesses::MachineProcesses()
{
    this->processList = new unordered_map<pid_t, Process *>();
}

void MachineProcesses::addProcess(Process *process)
{
    this->processList->insert(make_pair(process->getPid(), process));
}

void MachineProcesses::toString()
{
    for (auto &it : *(this->processList))
    {
        cout << setw(10) << left << it.first
             << setw(10) << left << it.second->getPpid()
             << setw(10) << left << it.second->getMemoryUsage()
             << setw(6) << left << it.second->getState()
             << setw(20) << left << convertSecondsToVisibleDuration(it.second->getElapsedSec())
             << setw(6) << left << setprecision (1) << fixed << it.second->getUsagePercentage()
             << setw(10) << left << it.second->getNumThreads()
             << setw(30) << left << it.second->getCmdLine() << endl;
    }
}

void MachineProcesses::constructProcessList()
{
    list<pid_t> *pids_list = getCurrentProcessesPIDs();
    this->uptime = getCPUUptime();

    for (auto &pid : *pids_list)
    {
        PULL_STATUS status = ERROR;
        memory_t process_memory = pullMemoryUsageByPID(pid, status);
        string cmdLine = getProcessCmdLine(pid);
        process_stats processStat = getProcessStat(pid);

        // ---------------------- go to static method or utils 
        second_t utime_sec = processStat.utime / sysconf(_SC_CLK_TCK);
        second_t stime_sec = processStat.stime / sysconf(_SC_CLK_TCK);
        second_t starttime_sec = processStat.starttime / sysconf(_SC_CLK_TCK);

        second_t elapsed_sec = this->uptime - starttime_sec;
        second_t usage_sec = utime_sec + stime_sec;
        float process_usage = usage_sec * 100.0 / (float)elapsed_sec;
        // ----- end of process processing

        if (status == SUCCESS)
        {
            Process *process = new Process(process_memory, pid, cmdLine, processStat.state, processStat.ppid, processStat.num_threads, elapsed_sec, process_usage);
            this->addProcess(process);
        }
    }
}

void MachineProcesses::updateProcessList()
{
    // TODO: just run for new to destruct the list then reconstruct again
    this->processList->clear();
    this->constructProcessList();
}

second_t MachineProcesses::getUptime()
{
    return this->uptime;
}

unordered_map<pid_t, Process *> *MachineProcesses::getProcessList()
{
    return this->processList;
}
