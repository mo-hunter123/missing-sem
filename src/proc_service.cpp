#include "../include/proc_service.h"
#include <string>
#include <string.h>
#include <fstream>
#include <iostream>

using namespace std;

machine_memory pullMachineMemoryInformations()
{
    string token;
    ifstream file(PROCMEMINFO);

    memory_t totalMemory = 0;
    memory_t freeMemory = 0;
    memory_t availableMemory = 0;

    if (!file)
    {
        cout << "Could not open " << PROCMEMINFO << endl;
        cout << strerror(errno) << endl;
        exit(-1);
    }

    else
    {
        while (file >> token)
        {
            if (token == MEMTOTAL_TOKEN)
            {
                file >> totalMemory;
            }
            else if (token == MEMAVAILABLE_TOKEN)
            {
                file >> availableMemory;
            }
            else if (token == MEMFREE_TOKEN)
            {
                file >> freeMemory;
            }
        }
        return {totalMemory, freeMemory, availableMemory};
    }
    file.close();
}

memory_t pullMemoryUsageByPID(pid_t pid)
{
    string token;
    memory_t rss;

    // TODO: - check if the process has the smaps_rollup or not,
    //       - check for file permissions 
    //       - if not the case use /proc/[pid]/smaps
    //          - by going through the file and add all found rss
    // TODO: refactor file opening to have a function returning an ifstream

    string smaps_rollup_file = PROCDIR + string("/") + to_string(pid) + PROCSMAPSROLLUP;

    ifstream file(smaps_rollup_file);

    if (!file)
    {
        cout << "Could not open " << PROCSMAPSROLLUP << endl;
        cout << strerror(errno) << endl;
        exit(-1);
    }
    else
    {
        while (file >> token)
        {
            if (token == RSS_TOKEN)
            {
                file >> rss;
                file.close();
                return rss;
            }
        }

        return NO_MEM_MEASURE;
    }
}
