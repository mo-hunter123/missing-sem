#include "Process.h"
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
    unordered_map<pid_t, Process *> *processList;

public:
    MachineProcesses();
    void addProcess(Process *process);
    void toString();
    void constructProcessList();
    void updateProcessList();
};
