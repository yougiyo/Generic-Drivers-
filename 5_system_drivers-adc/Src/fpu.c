/**
 * @file fpu.c
 * @brief FPU driver implementation for STM32F401RE.
 * @details Writes SCB->CPACR so CP10 and CP11 are configured for full access.
 * @author yougiyo
 * @date September 22, 2026
 */

#include "fpu.h"

/*
 * @brief Enable CP10 and CP11 coprocessors for full floating-point access.
 */
void fpu_enable(void)
{
    /* Set SCB_CPACR CP10 and CP11 fields to 0b11 (full access) for Cortex-M4F FPU. */
    SCB->CPACR |= ((3UL << 20U) | (3UL << 22U));
}
