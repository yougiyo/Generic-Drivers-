/**
 * @file adc.c
 * @brief ADC driver implementation for STM32F401RE.
 * @details Uses ADC1 (primary ADC instance) to sample PA1 / channel 1.
 * @author yougiyo
 * @date September 22, 2026
 */

#include "adc.h"
#include "stm32f4xx.h"

#define GPIOAEN         (1U << 0)
#define ADC1EN          (1U << 8)
#define ADC_CH1         (1U << 0)
#define AD_SEQ_LEN_1    (0x00U)
#define CR2_ADON        (1U << 0)
#define CR2_CONT        (1U << 1)
#define CR2_SWSTART     (1U << 30)
#define SR_EOC          (1U << 1)

/*
 * @brief Initialize PA1 and ADC1 for single-channel conversion on channel 1.
 */
void pa1_adc_init(void)
{
    /* Enable GPIOA clock in RCC_AHB1ENR for PA1 analog input configuration. */
    RCC->AHB1ENR |= GPIOAEN;

    /* Set PA1 mode to analog in GPIOA_MODER to connect pin to ADC front-end. */
    GPIOA->MODER |= (3U << 2);

    /* Enable ADC1 clock in RCC_APB2ENR (ADC1 is the primary ADC on STM32F401RE). */
    RCC->APB2ENR |= ADC1EN;

    /* Program ADC1_SQR3 with channel 1 as first conversion in the regular sequence. */
    ADC1->SQR3 = ADC_CH1;

    /* Program ADC1_SQR1 for a regular sequence length of 1 conversion. */
    ADC1->SQR1 = AD_SEQ_LEN_1;

    /* Enable ADC1 by setting ADON in ADC1_CR2. */
    ADC1->CR2 |= CR2_ADON;
}

/*
 * @brief Enable continuous conversion mode and trigger ADC1 software start.
 */
void start_conversion(void)
{
    /* Set CONT in ADC1_CR2 for continuous conversion mode. */
    ADC1->CR2 |= CR2_CONT;

    /* Set SWSTART in ADC1_CR2 to launch regular conversions. */
    ADC1->CR2 |= CR2_SWSTART;
}

/*
 * @brief Poll for end-of-conversion and return the ADC1 data register value.
 */
uint32_t adc_read(void)
{
    /* Wait for EOC flag in ADC1_SR to indicate conversion completion. */
    while ((ADC1->SR & SR_EOC) == 0U)
    {
    }

    /* Return the converted sample from ADC1_DR. */
    return ADC1->DR;
}
