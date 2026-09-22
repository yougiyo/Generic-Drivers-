/**
 * @file timebase.c
 * @brief SysTick timebase driver implementation for STM32F401RE.
 * @details Configures SysTick for a 1 ms interrupt period at an 84 MHz core clock.
 * @author yougiyo
 * @date September 22, 2026
 */

#include "timebase.h"
#include "stm32f4xx.h"

#define CTRL_ENABLE         (1U << 0)
#define CTRL_TICKINT        (1U << 1)
#define CTRL_CLKSRC         (1U << 2)

#define SYS_CLOCK_HZ        (84000000U)
#define TICK_FREQ_HZ        (1000U)
#define SYSTICK_LOAD_1MS    ((SYS_CLOCK_HZ / TICK_FREQ_HZ) - 1U)

volatile uint32_t g_curr_tick;

static void tick_increment(void);

/*
 * @brief Block the CPU for the requested number of milliseconds.
 */
void delay(uint32_t delay)
{
    uint32_t tickstart = get_tick();

    while ((get_tick() - tickstart) < delay)
    {
    }
}

/*
 * @brief Return the current millisecond tick snapshot.
 */
uint32_t get_tick(void)
{
    return g_curr_tick;
}

/*
 * @brief Increment the global millisecond tick counter.
 */
static void tick_increment(void)
{
    g_curr_tick++;
}

/*
 * @brief Configure SysTick for 1 ms interrupts at 84 MHz system clock.
 */
void timebase_init(void)
{
    /* Disable global interrupts while SysTick registers are configured. */
    __disable_irq();

    /* Program SysTick_LOAD with cycles-per-millisecond (84,000 - 1). */
    SysTick->LOAD = SYSTICK_LOAD_1MS;

    /* Clear SysTick_VAL to reset the current down-counter value. */
    SysTick->VAL = 0U;

    /* Select processor clock as SysTick source in SysTick_CTRL. */
    SysTick->CTRL = CTRL_CLKSRC;

    /* Enable SysTick interrupt generation in SysTick_CTRL. */
    SysTick->CTRL |= CTRL_TICKINT;

    /* Enable SysTick counter in SysTick_CTRL. */
    SysTick->CTRL |= CTRL_ENABLE;

    /* Re-enable global interrupts after SysTick setup is complete. */
    __enable_irq();
}

/*
 * @brief SysTick interrupt service routine.
 */
void SysTick_Handler(void)
{
    tick_increment();
}
