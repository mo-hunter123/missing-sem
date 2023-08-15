#include <iostream>
#include <unistd.h>
#include <iomanip>

#include "../include/Machine.h"
#include "../include/utils.h"

using namespace std;

// TODO: make it dynamic
#define REFRESH_RATE 4 // the real time refresh rate in seconds
#define GB_TO_KB 1000000

int main(int argc, char const *argv[])
{
    Machine *host = new Machine();
    host->init();

    while (true)
    {
        machine_memory currentMemoryState = host->getMachineMemory()->getCurrentMemory();
        memory_t usedMemory = currentMemoryState.totalMemory - currentMemoryState.availableMemory;
        float cpuUsage = host->getMachineProcesses()->getCpuUsage();

        system("clear");
        cout << "--------------------------------------" << endl;
        cout << "Memory         : " << (float)usedMemory / (float)GB_TO_KB << " GB / " << (float)currentMemoryState.totalMemory / (float)GB_TO_KB << " GB" << endl;
        cout << "Uptime         : " << convertSecondsToVisibleDuration(convertClockTicksToSeconds(host->getMachineProcesses()->getCPUData()->getTotalTime())) << endl;
        cout << "Cpu Usage      : " << cpuUsage << " %" << endl;
        cout << "Cpu free       : " << (100 - cpuUsage) << " %" << endl;
        cout << "--------------------------------------" << endl;

        cout << setw(10)    << left << "PID"
             << setw(10)    << left << "PPID"
             << setw(10)    << left << "MEM"
             << setw(6)     << left << "STAT"
             << setw(20)    << left << "TIME"
             << setw(6)     << left << "CPU%"
             << setw(10)    << left << "THREADS"
             << setw(30)    << left << "Command" 
             << endl;

        host->getMachineProcesses()->toString();
        sleep(REFRESH_RATE);
        host->updateMachineMetrics();
    }

    return 0;
}
