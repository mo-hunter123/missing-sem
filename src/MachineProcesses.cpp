#include "MachineProcesses.h"
#include <iomanip>


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
        std::cout << left << setw(10) << it.first << left << it.second->getMemoryUsage() << endl;
    }
}

void MachineProcesses::constructProcessList()
{
    list<pid_t> *pids_list = getCurrentProcessesPIDs();

    for (auto &pid : *pids_list)
    {
        PULL_STATUS status = ERROR;
        memory_t process_memory = pullMemoryUsageByPID(pid, status);

        if (status == SUCCESS)
        {
            Process *process = new Process(process_memory, pid);
            this->addProcess(process);
        }
    }
}