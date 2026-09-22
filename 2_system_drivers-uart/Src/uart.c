/**
 * @file uart.c
 * @brief UART driver implementation for STM32F401RE.
 * @details Configures USART2 TX on PA2 at 115200 baud, 8N1, for Nucleo-F401RE VCP.
 * @author yougiyo
 * @date September 22, 2026
 */

#include <stdint.h>
#include "uart.h"

#define GPIOAEN             (1U << 0)
#define USART2EN            (1U << 17)
#define USART2_AF7          (0x7U)
#define USART2_TX_PIN       (2U)

#define DBG_UART_BAUDRATE   (115200U)
#define APB1_CLK_HZ         (42000000U)

#define CR1_TE              (1U << 3)
#define CR1_RE              (1U << 2)
#define CR1_UE              (1U << 13)
#define CR1_M               (1U << 12)
#define CR1_PCE             (1U << 10)
#define CR2_STOP            (3U << 12)
#define SR_TXE              (1U << 7)

static uint16_t compute_uart_bd(uint32_t periph_clk, uint32_t baudrate);
static void uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate);
static void uart_write(int ch);

/*
 * @brief Retarget printf output to USART2.
 */
int __io_putchar(int ch)
{
    uart_write(ch);
    return ch;
}

/*
 * @brief Initialize USART2 with the Nucleo-F401RE default 115200-8N1 configuration.
 */
void debug_uart_init(void)
{
    /* Enable GPIOA clock in RCC_AHB1ENR for USART2 PA2 alternate-function pin. */
    RCC->AHB1ENR |= GPIOAEN;

    /* Set PA2 mode to alternate function in GPIOA_MODER. */
    GPIOA->MODER &= ~(3U << (USART2_TX_PIN * 2U));
    GPIOA->MODER |= (2U << (USART2_TX_PIN * 2U));

    /* Select AF7 (USART2_TX) for PA2 in GPIOA_AFRL. */
    GPIOA->AFR[0] &= ~(0xFU << (USART2_TX_PIN * 4U));
    GPIOA->AFR[0] |= (USART2_AF7 << (USART2_TX_PIN * 4U));

    /* Enable USART2 peripheral clock in RCC_APB1ENR. */
    RCC->APB1ENR |= USART2EN;

    /* Program USART2_BRR for 115200 baud (APB1 assumed at 42 MHz for 84 MHz SYSCLK setup). */
    uart_set_baudrate(APB1_CLK_HZ, DBG_UART_BAUDRATE);

    /* Clear M/PCE bits in USART2_CR1 to enforce 8 data bits and no parity. */
    USART2->CR1 &= ~(CR1_M | CR1_PCE);

    /* Clear STOP bits in USART2_CR2 to select 1 stop bit. */
    USART2->CR2 &= ~CR2_STOP;

    /* Enable transmitter and receiver in USART2_CR1. */
    USART2->CR1 |= (CR1_TE | CR1_RE);

    /* Enable USART2 module in USART2_CR1. */
    USART2->CR1 |= CR1_UE;
}

/*
 * @brief Transmit one byte over USART2 in polling mode.
 */
static void uart_write(int ch)
{
    /* Wait until TXE is set in USART2_SR so USART2_DR can accept new data. */
    while ((USART2->SR & SR_TXE) == 0U)
    {
    }

    /* Write the outgoing byte to USART2_DR. */
    USART2->DR = (uint8_t)(ch & 0xFF);
}

/*
 * @brief Compute BRR divider value from peripheral clock and baudrate.
 */
static uint16_t compute_uart_bd(uint32_t periph_clk, uint32_t baudrate)
{
    return (uint16_t)((periph_clk + (baudrate / 2U)) / baudrate);
}

/*
 * @brief Update USART2_BRR with the computed baudrate divider.
 */
static void uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate)
{
    /* Write BRR so USART2 operates at the requested baudrate. */
    USART2->BRR = compute_uart_bd(periph_clk, baudrate);
}
