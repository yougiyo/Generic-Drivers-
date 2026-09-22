/**
 * @file bsp.c
 * @brief GPIO board-support driver implementation for STM32F401RE.
 * @details Implements user LED control on PA5 and user button readout on PC13.
 * @author yougiyo
 * @date September 22, 2026
 */

#include "bsp.h"
#include "stm32f4xx.h"

#define GPIOAEN     (1U << 0)
#define GPIOCEN     (1U << 2)

#define LED_PIN     (1U << 5)
#define BTN_PIN     (1U << 13)

/*
 * @brief Configure PA5 as digital output for the Nucleo-F401RE user LED.
 */
void led_init(void)
{
    /* Enable GPIOA clock in RCC_AHB1ENR so PA5 configuration writes take effect. */
    RCC->AHB1ENR |= GPIOAEN;

    /* Set PA5 to general-purpose output mode in GPIOA_MODER. */
    GPIOA->MODER &= ~(3U << 10);
    GPIOA->MODER |= (1U << 10);
}

/*
 * @brief Set PA5 high to turn on the Nucleo-F401RE user LED.
 */
void led_on(void)
{
    /* Set PA5 output data bit in GPIOA_ODR. */
    GPIOA->ODR |= LED_PIN;
}

/*
 * @brief Clear PA5 to turn off the Nucleo-F401RE user LED.
 */
void led_off(void)
{
    /* Clear PA5 output data bit in GPIOA_ODR. */
    GPIOA->ODR &= ~LED_PIN;
}

/*
 * @brief Configure PC13 as input for the Nucleo-F401RE user button.
 */
void button_init(void)
{
    /* Enable GPIOC clock in RCC_AHB1ENR for PC13 button input access. */
    RCC->AHB1ENR |= GPIOCEN;

    /* Set PC13 to input mode in GPIOC_MODER. */
    GPIOC->MODER &= ~(3U << 26);
}

/*
 * @brief Return true when the active-low PC13 user button is pressed.
 */
bool get_btn_state(void)
{
    return ((GPIOC->IDR & BTN_PIN) == 0U);
}
