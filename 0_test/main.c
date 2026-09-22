#include <stdio.h>
#include <stdint.h>
#include "fpu.h"
#include "uart.h"
#include "timebase.h"
#include "bsp.h"
#include "adc.h"

int main(void)
{
    uint32_t adc_value = 0U;

    /* Enable CP10/CP11 so the Cortex-M4F can execute floating-point instructions. */
    fpu_enable();

    /* Configure USART2 (PA2 TX) for 115200 8N1 on the ST-LINK Virtual COM Port. */
    debug_uart_init();

    /* Configure SysTick for a 1 ms time base (assumes an 84 MHz system clock). */
    timebase_init();

    /* Configure Nucleo-F401RE user LED on PA5 as a push-pull output. */
    led_init();

    /* Configure the user button on PC13 (active low) as a digital input. */
    button_init();

    /* Configure ADC1 channel 1 on PA1 and start continuous conversions. */
    pa1_adc_init();
    start_conversion();

    printf("Hello from STM32F401RE\r\n");

    while (1)
    {
        /* Read the latest ADC1 sample and print it over USART2/VCP. */
        adc_value = adc_read();
        printf("ADC1 CH1 = %lu\r\n", (unsigned long)adc_value);

        /* Blink the user LED with a 1 ms-tick based delay helper. */
        led_on();
        delay(250U);
        led_off();
        delay(250U);
    }
}
