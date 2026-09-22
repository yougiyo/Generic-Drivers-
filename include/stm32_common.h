#ifndef STM32_COMMON_H
#define STM32_COMMON_H

#include <stdint.h>

#define MMIO32(addr) (*(volatile uint32_t *)(addr))

#define SET_BIT(REG, BIT) ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT) ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT) ((REG) & (BIT))

#endif
