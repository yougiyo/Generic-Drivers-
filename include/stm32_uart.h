#ifndef STM32_UART_H
#define STM32_UART_H

#include <stdint.h>

typedef struct {
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} USART_TypeDef;

#define USART1 ((USART_TypeDef *)0x40011000u)

void STM32_UART_Init(USART_TypeDef *uart, uint32_t peripheral_clock_hz, uint32_t baudrate);
void STM32_UART_SendByte(USART_TypeDef *uart, uint8_t data);
uint8_t STM32_UART_ReadByte(USART_TypeDef *uart);

#endif
