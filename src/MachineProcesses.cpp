#include "MachineProcesses.h"
#include <iomanip>
#include <unistd.h>
#include "utils.h"
#include "../include/proc_service.h"

MachineProcesses::MachineProcesses()
{
    this->processList = new unordered_map<pid_t, Process *>();
    lastCpuRecord = new CPUData(0, 0, 0, 0, 0, 0, 0, 0);
}

MachineProcesses::MachineProcesses(CPUData *machineCpu,
                                   CPUData *lastCpuRecord,
                                   unordered_map<pid_t, Process *> *processList)
{
    this->processList = processList;
    this->lastCpuRecord = lastCpuRecord;
    this->machineCpu = machineCpu;
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
             << setw(6) << left << setprecision(1) << fixed << it.second->getUsagePercentage()
             << setw(10) << left << it.second->getNumThreads()
             << setw(30) << left << it.second->getCmdLine() << endl;
    }
}

void MachineProcesses::constructProcessList()
{
    list<pid_t> *pids_list = getCurrentProcessesPIDs();

    this->machineCpu = pullProcStats();
    second_t uptime = getCPUUptime();

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

        second_t elapsed_sec = uptime - starttime_sec;
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
    this->lastCpuRecord = new CPUData(*(this->machineCpu));
    // TODO: just run for new to destruct the list then reconstruct again
    delete this->machineCpu;
    this->processList->clear();
    this->constructProcessList();
}

clktck_t MachineProcesses::getCpuDelta()
{
    return this->machineCpu->getTotalTime() - this->lastCpuRecord->getTotalTime();
}

float MachineProcesses::getCpuUsage()
{
    clktck_t delta_cpu = this->getCpuDelta();

    clktck_t idle_delta = this->getCPUData()->getTotalIdle() - this->getLastCpuRecord()->getTotalIdle();
    clktck_t used_cpu = delta_cpu - idle_delta;
    float cpu_usage = (100.0 * used_cpu) / (float)delta_cpu;

    return cpu_usage;
}

CPUData *MachineProcesses::getCPUData()
{
    return this->machineCpu;
}

CPUData *MachineProcesses::getLastCpuRecord()
{
    return this->lastCpuRecord;
}

unordered_map<pid_t, Process *> *MachineProcesses::getProcessList()
{
    return this->processList;
}
