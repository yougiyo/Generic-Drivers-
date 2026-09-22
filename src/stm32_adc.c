#include "stm32_adc.h"

#define ADC_CR2_ADON (1u << 0)
#define ADC_CR2_SWSTART (1u << 30)
#define ADC_SR_EOC (1u << 1)

void STM32_ADC_InitSingleChannel(ADC_TypeDef *adc, uint8_t channel)
{
    adc->SQR1 = 0u;
    adc->SQR2 = 0u;
    adc->SQR3 = (uint32_t)(channel & 0x1Fu);
    adc->CR2 |= ADC_CR2_ADON;
}

uint16_t STM32_ADC_ReadSingle(ADC_TypeDef *adc)
{
    adc->CR2 |= ADC_CR2_SWSTART;
    while ((adc->SR & ADC_SR_EOC) == 0u) {
    }
    return (uint16_t)(adc->DR & 0xFFFFu);
}
