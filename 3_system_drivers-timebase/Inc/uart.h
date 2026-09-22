/**
 * @file uart.h
 * @brief UART driver interface for STM32F401RE.
 * @details Configures USART2 for 115200 baud, 8 data bits, no parity, and 1 stop bit.
 * @author yougiyo
 * @date September 22, 2026
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f4xx.h"

/**
 * @brief Initialize USART2 for ST-LINK Virtual COM Port communication.
 * @param None
 * @return None
 */
void debug_uart_init(void);

#endif /* UART_H_ */
