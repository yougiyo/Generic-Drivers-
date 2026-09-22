#include "stm32_gpio.h"

void STM32_GPIO_SetPinMode(GPIO_TypeDef *port, uint8_t pin, GPIO_Mode mode)
{
    const uint32_t shift = (uint32_t)pin * 2u;
    port->MODER &= ~(0x3u << shift);
    port->MODER |= ((uint32_t)mode << shift);
}

void STM32_GPIO_WritePin(GPIO_TypeDef *port, uint8_t pin, uint8_t value)
{
    if (value != 0u) {
        port->BSRR = (1u << pin);
    } else {
        port->BSRR = (1u << (pin + 16u));
    }
}

uint8_t STM32_GPIO_ReadPin(GPIO_TypeDef *port, uint8_t pin)
{
    return (uint8_t)((port->IDR >> pin) & 0x1u);
}
