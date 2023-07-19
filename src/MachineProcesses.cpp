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
        cout << setw(15) << left << it.first
             << setw(15) << left << it.second->getMemoryUsage()
             << setw(30) << left << it.second->getCmdLine() << endl;
    }
}

void MachineProcesses::constructProcessList()
{
    list<pid_t> *pids_list = getCurrentProcessesPIDs();

    for (auto &pid : *pids_list)
    {
        PULL_STATUS status = ERROR;
        memory_t process_memory = pullMemoryUsageByPID(pid, status);
        string cmdLine = getProcessCmdLine(pid);

        if (status == SUCCESS)
        {
            Process *process = new Process(process_memory, pid, cmdLine);
            this->addProcess(process);
        }
    }
}

void MachineProcesses::updateProcessList() {
    // TODO: just run for new to destruct the list then reconstruct again 
    this->processList->clear();
    this->constructProcessList();
}