#ifndef CPU_DATA_H
#define CPU_DATA_H

#include "types.h"

class CPUData
{

private:
    clktck_t user_time;     // user mode
    clktck_t nice_time;     // user mode with nice priority (low)
    clktck_t system_time;   // system mode
    clktck_t idle_time;     // spent time in idle task
    clktck_t iowait_time;   // waiting I/O to complete
    clktck_t irq;           // Time servicing interrupts. 
    clktck_t softirq;       // Time servicing softirqs
    clktck_t steal_time;    // spent time in other OS in vertualised env

public:
    CPUData(clktck_t user_time,
            clktck_t nice_time,
            clktck_t system_time,
            clktck_t idle_time,
            clktck_t iowait_time,
            clktck_t irq,
            clktck_t softirq,
            clktck_t steal_time);

    clktck_t getUserTime();
    clktck_t getNiceTime();
    clktck_t getSystemTime();
    clktck_t getIdleTime();
    clktck_t getIowaitTime();
    clktck_t getIrq();
    clktck_t getSoftirq();
    clktck_t getStealTime();

    clktck_t getTotalTime();
    clktck_t getTotalIdle();
};

#endif
