#include "proc_service.h"

using namespace std;

class Process
{

private:
    memory_t memoryUsage;
    pid_t pid;

public:
    Process(memory_t memoryUsage, pid_t pid);
    string toString();
};