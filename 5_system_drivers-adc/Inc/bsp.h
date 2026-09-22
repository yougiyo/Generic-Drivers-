/**
 * @file bsp.h
 * @brief GPIO board-support driver interface for STM32F401RE.
 * @details Provides LED and user-button helpers for Nucleo-F401RE (PA5 LED, PC13 button).
 * @author yougiyo
 * @date September 22, 2026
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Initialize Nucleo-F401RE user LED pin (PA5) as output.
 * @param None
 * @return None
 */
void led_init(void);

/**
 * @brief Drive the Nucleo-F401RE user LED pin (PA5) high.
 * @param None
 * @return None
 */
void led_on(void);

/**
 * @brief Drive the Nucleo-F401RE user LED pin (PA5) low.
 * @param None
 * @return None
 */
void led_off(void);

/**
 * @brief Initialize Nucleo-F401RE user button pin (PC13) as input.
 * @param None
 * @return None
 */
void button_init(void);

/**
 * @brief Read Nucleo-F401RE user button state (PC13, active low).
 * @param None
 * @return true if pressed, false otherwise.
 */
bool get_btn_state(void);

#endif /* GPIO_H_ */
