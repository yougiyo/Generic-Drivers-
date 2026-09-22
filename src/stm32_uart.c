#include "stm32_uart.h"

#define USART_SR_RXNE (1u << 5)
#define USART_SR_TXE (1u << 7)
#define USART_CR1_UE (1u << 13)
#define USART_CR1_TE (1u << 3)
#define USART_CR1_RE (1u << 2)

void STM32_UART_Init(USART_TypeDef *uart, uint32_t peripheral_clock_hz, uint32_t baudrate)
{
    uart->BRR = (peripheral_clock_hz + (baudrate / 2u)) / baudrate;
    uart->CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}

void STM32_UART_SendByte(USART_TypeDef *uart, uint8_t data)
{
    while ((uart->SR & USART_SR_TXE) == 0u) {
    }
    uart->DR = data;
}

uint8_t STM32_UART_ReadByte(USART_TypeDef *uart)
{
    while ((uart->SR & USART_SR_RXNE) == 0u) {
    }
    return (uint8_t)(uart->DR & 0xFFu);
}
