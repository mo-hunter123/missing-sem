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

memory_t pullMemoryUsageByPID(pid_t pid, PULL_STATUS &status)
{
    string token;
    memory_t rss;

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

string getProcessCmdLine(pid_t pid)
{
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

second_t getCPUUptime()
{
    second_t uptime;
    ifstream file(UPTIME);

    if (!file)
    {
        cout << "Could not open " << UPTIME << endl;
        cout << strerror(errno) << endl;
        return -1;
    }
    else
    {
        file >> uptime;
        file.close();
        return uptime;
    }
}

void updateProcessStat(process_stats *processStat, unsigned int count, string token)
{
    switch (count)
    {
    case PROC_STAT_INDEX:
        processStat->state = token[0];
        break;
    case PROC_PPID_INDEX:
        processStat->ppid = stoi(token);
        break;
    case PROC_UTIME_INDEX:
        processStat->utime = stoi(token);
        break;
    case PROC_STIME_INDEX:
        processStat->stime = stoi(token);
        break;
    case PROC_THREADS_INDEX:
        processStat->num_threads = stoi(token);
        break;
    case PROC_STARTTIME_INDEX:
        processStat->starttime = stoi(token);
        break;
    default:
        break;
    }
}

process_stats getProcessStatFromFile(istringstream &stream)
{
    string token;
    unsigned int count = 1;
    process_stats processStat = {'N', 0, 0};
    while (stream >> token)
    {
        updateProcessStat(&processStat, count, token);
        count += 1;
    }

    return processStat;
}

process_stats getProcessStatFromFile(ifstream &stream)
{
    string token;
    unsigned int count = 1;
    process_stats processStat = {'N', 0, 0};
    while (stream >> token)
    {
        updateProcessStat(&processStat, count, token);
        count += 1;
    }

    return processStat;
}

process_stats getProcessStat(pid_t pid)
{
    string proc_stat_file = PROCDIR + string("/") + to_string(pid) + PROCSTAT;
    ifstream file(proc_stat_file);
    process_stats processStat;

    if (!file)
    {
        cout << "Could not open " << proc_stat_file << endl;
        cout << strerror(errno) << endl;
    }
    else
    {
        processStat = getProcessStatFromFile(file);
    }

    return processStat;
}

CPUData* pullProcStats()
{

    ifstream file(PROCSTATDIR);

    if (!file)
    {
        cout << "Could not open " << PROCSTATDIR << endl;
        cout << strerror(errno) << endl;
        exit(-1);
    }
    // for the moment we will get only the first line that aggregates all cpus numbers
    string allCpusLine;

    getline(file, allCpusLine);

    return processCPUStat(allCpusLine);
}

CPUData* processCPUStat(string allCpusLine)
{
    string cpuString;
    clktck_t user_time = 0;
    clktck_t nice_time = 0;
    clktck_t system_time = 0;
    clktck_t idle_time = 0;
    clktck_t iowait_time = 0;
    clktck_t irq = 0;
    clktck_t softirq = 0;
    clktck_t steal_time = 0;
    
    istringstream procStatStream(allCpusLine);
    if (!(procStatStream >> cpuString >> user_time >> nice_time >> system_time >> idle_time >> iowait_time >>  irq >> softirq >> steal_time))
    {
        cout << "Error reading stat cpu data" << endl;
        exit(-1);
    }

    return new CPUData(user_time,
                       nice_time,
                       system_time,
                       idle_time,
                       iowait_time,
                       irq,
                       softirq,
                       steal_time);
}
