#pragma once
#include "hal/hal.h"
#include "Config.h"

// Configuration - set before including
#ifndef SYSTEM_TICK_HZ
#define SYSTEM_TICK_HZ 1000 // Default 1kHz
#endif

struct tickerStat_t{
    uint16_t actualFreq;
    int32_t error_ppm;
};

inline tickerStat_t tickerStat;

//SYSTEM TICKER TIMER2
#define TICK_TO_uS(ticks)((ticks*1000000.0)/SYSTEM_TICK_HZ)
#define TICK_TO_mS(ticks)((ticks*1000.0)/SYSTEM_TICK_HZ)
#define TICK_TO_S(ticks)((ticks)/SYSTEM_TICK_HZ)

#define S_TO_TICK(s)((s*SYSTEM_TICK_HZ))
#define mS_TO_TICK(ms)((ms*SYSTEM_TICK_HZ)/1000.0)
#define uS_TO_TICK(us)((us*SYSTEM_TICK_HZ)/1000000.0)

void sysTIM_init();
uint32_t getTicks();

static inline void sys_init(void) {
    sysTIM_init();
    // Additional system initialization can be added here
}