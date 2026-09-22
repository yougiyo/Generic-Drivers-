#include "stm32_timebase.h"
#include "stm32_common.h"

#define SYST_CSR MMIO32(0xE000E010u)
#define SYST_RVR MMIO32(0xE000E014u)
#define SYST_CVR MMIO32(0xE000E018u)

#define SYST_CSR_ENABLE (1u << 0)
#define SYST_CSR_TICKINT (1u << 1)
#define SYST_CSR_CLKSOURCE (1u << 2)

static volatile uint32_t g_ms_ticks;

void SysTick_Handler(void)
{
    g_ms_ticks++;
}

void STM32_TimeBase_Init(uint32_t cpu_clock_hz)
{
    SYST_RVR = (cpu_clock_hz / 1000u) - 1u;
    SYST_CVR = 0u;
    SYST_CSR = SYST_CSR_CLKSOURCE | SYST_CSR_TICKINT | SYST_CSR_ENABLE;
}

uint32_t STM32_TimeBase_Millis(void)
{
    return g_ms_ticks;
}

void STM32_TimeBase_DelayMs(uint32_t delay_ms)
{
    const uint32_t start = STM32_TimeBase_Millis();
    while ((STM32_TimeBase_Millis() - start) < delay_ms) {
    }
}
