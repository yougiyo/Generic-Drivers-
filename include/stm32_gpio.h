#ifndef STM32_GPIO_H
#define STM32_GPIO_H

#include <stdint.h>

typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
} GPIO_TypeDef;

#define GPIOA ((GPIO_TypeDef *)0x40020000u)
#define GPIOB ((GPIO_TypeDef *)0x40020400u)
#define GPIOC ((GPIO_TypeDef *)0x40020800u)

typedef enum {
    GPIO_MODE_INPUT = 0u,
    GPIO_MODE_OUTPUT = 1u,
    GPIO_MODE_ALT = 2u,
    GPIO_MODE_ANALOG = 3u
} GPIO_Mode;

void STM32_GPIO_SetPinMode(GPIO_TypeDef *port, uint8_t pin, GPIO_Mode mode);
void STM32_GPIO_WritePin(GPIO_TypeDef *port, uint8_t pin, uint8_t value);
uint8_t STM32_GPIO_ReadPin(GPIO_TypeDef *port, uint8_t pin);

#endif
