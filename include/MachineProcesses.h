#ifndef MACHINE_PROC_H
#define MACHINE_PROC_H

#include "Process.h"
#include "CPUData.h"
#include "types.h"
#include <unordered_map>
#include <iostream>

using namespace std;

/**
 * @brief Singleton class that will contain the process list in a hashtable form
 *
 */

// TODO: make it singleton
class MachineProcesses
{
private:
    CPUData *machineCpu;
    CPUData *lastCpuRecord;
    unordered_map<pid_t, Process *> *processList;

public:
    MachineProcesses();
    MachineProcesses(CPUData *machineCpu,
                     CPUData *lastCpuRecord, 
                     unordered_map<pid_t, Process *> *processList);
    void addProcess(Process *process);
    void toString();
    void constructProcessList();
    void updateProcessList();
    clktck_t getCpuDelta();
    float getCpuUsage();
    CPUData *getCPUData();
    CPUData *getLastCpuRecord();
    unordered_map<pid_t, Process *> *getProcessList();
};

#endif
