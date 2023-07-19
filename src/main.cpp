#include <iostream>
#include <unistd.h>
#include <iomanip>

#include "../include/Machine.h"
#include "../include/utils.h"

using namespace std;

// TODO: make it dynamic 
#define REFRESH_RATE 4 // the real time refresh rate in seconds 

int main(int argc, char const *argv[])
{
    Machine *host = new Machine();
    host->init();

    // cout << left << setw(10) << "PID" << left << setw(5) << "Memory usage" << left << setw(8) <<  "Command line" << left << setw(5) << endl;

    while (true)
    {
        system("clear");
        cout << "-------------------"   << endl;
        cout << "Available Mem : "      << host->getMachineMemory()->getCurrentMemory().availableMemory << endl;
        cout << "Free Mem : "           << host->getMachineMemory()->getCurrentMemory().freeMemory << endl;
        cout << "Total Mem : "          << host->getMachineMemory()->getCurrentMemory().totalMemory << endl;
        cout << "Uptime : "             << convertSecondsToVisibleDuration(host->getMachineProcesses()->getUptime()) << endl;
        cout << "-------------------"   << endl;

        cout << setw(15) << left << "PID"
             << setw(15) << left << "MEM"
             << setw(30) << left << "Command" << endl;
        host->getMachineProcesses()->toString();
        sleep(REFRESH_RATE);
        host->getMachineProcesses()->updateProcessList();
    }

    return 0;
}
