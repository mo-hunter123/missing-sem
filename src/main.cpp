#include <iostream>
#include <unistd.h>
#include <iomanip>

#include "../include/Machine.h"

using namespace std;

int main(int argc, char const *argv[])
{
    Machine *host = new Machine();
    host->init();

    system("clear");
    cout << "-------------------" << endl;

    cout << left << setw(10) << "PID" << left << setw(5) << "Memory usage" << left << setw(8) << endl;
    host->getMachineProcesses()->toString();

    return 0;
}
