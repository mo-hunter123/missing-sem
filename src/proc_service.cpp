#include "../include/proc_service.h"
#include <string>
#include <string.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <array>
#include <memory>

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

memory_t pullMemoryUsageByPID(pid_t pid, PULL_STATUS& status)
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
        status = ERROR;
    }
    else
    {
        while (file >> token)
        {
            if (token == RSS_TOKEN)
            {
                file >> rss;
                status = SUCCESS;
                file.close();
                return rss;
            }
        }
    }
    status = ERROR;
    return NO_MEM_MEASURE;
}

list<string> *execute_linux_command(const char *cmd)
{
    std::array<char, 128> buffer;
    list<string> *command_result = new list<string>();
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
    {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        command_result->push_back(buffer.data());
    }
    return command_result;
}

list<pid_t> *getCurrentProcessesPIDs()
{
    list<string> *pid_str_list = execute_linux_command("ps -A -o pid --no-headers");
    list<pid_t> *pid_list = new list<pid_t>();

    for (auto &it : *pid_str_list)
    {
        pid_list->push_back(stoi(it));
    }

    return pid_list;
}

string getProcessCmdLine(pid_t pid) {
    string cmdline_file = PROCDIR + string("/") + to_string(pid) + PROCCMDLINE;
    string cmdLine; 

    ifstream file(cmdline_file);

    if (!file)
    {
        cout << "Could not open " << PROCCMDLINE << endl;
        cout << strerror(errno) << endl;
        return "N/A";
    }
    else
    {
        file >> cmdLine; 
        file.close();
        return cmdLine;
    }
}