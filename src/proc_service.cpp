#include "proc_service.h"
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
}
