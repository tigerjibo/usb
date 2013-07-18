#ifndef _TIMER_H_
#define _TIMER_H_

#include "lpc_types.h"

#define TIMER_PRIORITY 1

extern void Timer_Init();
extern void Timer_Delay(uint32_t delay);

#endif
