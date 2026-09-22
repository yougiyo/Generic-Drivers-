#include "stm32_fpu.h"
#include "stm32_common.h"

#define SCB_CPACR MMIO32(0xE000ED88u)
#define CP10_CP11_FULL_ACCESS ((3u << 20) | (3u << 22))

void STM32_FPU_Enable(void)
{
    SET_BIT(SCB_CPACR, CP10_CP11_FULL_ACCESS);
}
