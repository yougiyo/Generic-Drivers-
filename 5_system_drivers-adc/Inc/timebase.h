/**
 * @file timebase.h
 * @brief SysTick timebase driver interface for STM32F401RE.
 * @details Provides a 1 ms software tick and blocking millisecond delay helper.
 * @author yougiyo
 * @date September 22, 2026
 */

#ifndef TIMEBASE_H_
#define TIMEBASE_H_

#include <stdint.h>

/**
 * @brief Get the current software tick value in milliseconds.
 * @param None
 * @return Current tick count in milliseconds.
 */
uint32_t get_tick(void);

/**
 * @brief Block for a requested number of milliseconds.
 * @param delay Delay duration in milliseconds.
 * @return None
 */
void delay(uint32_t delay);

/**
 * @brief Configure SysTick to generate a 1 ms interrupt tick.
 * @param None
 * @return None
 */
void timebase_init(void);

#endif /* TIMEBASE_H_ */
