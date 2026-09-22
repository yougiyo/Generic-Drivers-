#ifndef STM32_TIMEBASE_H
#define STM32_TIMEBASE_H

#include <stdint.h>

void STM32_TimeBase_Init(uint32_t cpu_clock_hz);
uint32_t STM32_TimeBase_Millis(void);
void STM32_TimeBase_DelayMs(uint32_t delay_ms);

#endif
