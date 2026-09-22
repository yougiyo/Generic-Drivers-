/**
 * @file fpu.h
 * @brief FPU driver interface for STM32F401RE.
 * @details Enables Cortex-M4F CP10/CP11 full access for hardware floating-point instructions.
 * @author yougiyo
 * @date September 22, 2026
 */

#ifndef FPU_H_
#define FPU_H_

#include "stm32f4xx.h"

/**
 * @brief Enable full access to the Cortex-M4F floating-point unit.
 * @param None
 * @return None
 */
void fpu_enable(void);

#endif /* FPU_H_ */
