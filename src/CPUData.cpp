#include "../include/CPUData.h"

CPUData::CPUData(clktck_t user_time,
                 clktck_t nice_time,
                 clktck_t system_time,
                 clktck_t idle_time,
                 clktck_t iowait_time,
                 clktck_t irq,
                 clktck_t softirq,
                 clktck_t steal_time)
{
    this->user_time = user_time;
    this->nice_time = nice_time;
    this->system_time = system_time;
    this->idle_time = idle_time;
    this->iowait_time = iowait_time;
    this->irq = irq;
    this->softirq = softirq;
    this->steal_time = steal_time;
}

clktck_t CPUData::getUserTime()
{
    return this->user_time;
}

clktck_t CPUData::getNiceTime()
{
    return this->nice_time;
}

clktck_t CPUData::getSystemTime()
{
    return this->system_time;
}

clktck_t CPUData::getIdleTime()
{
    return this->idle_time;
}

clktck_t CPUData::getIowaitTime()
{
    return this->iowait_time;
}

clktck_t CPUData::getIrq()
{
    return this->irq;
}

clktck_t CPUData::getSoftirq()
{
    return this->softirq;
}

clktck_t CPUData::getStealTime()
{
    return this->steal_time;
}

clktck_t CPUData::getTotalTime()
{
    return this->user_time +
           this->nice_time +
           this->system_time +
           this->idle_time +
           this->iowait_time +
           this->irq +
           this->softirq +
           this->steal_time;
}

clktck_t CPUData::getTotalIdle()
{
    return this->idle_time + this->iowait_time;
}
