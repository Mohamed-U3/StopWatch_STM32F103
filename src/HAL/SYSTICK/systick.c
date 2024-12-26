#include "SYSTICK.h"

////////////////////////////////////////////////////////////////////////////////////
// U3 Edit - Function to return elapsed time in milliseconds
volatile static uint32_t milliseconds = 0;

// SysTick interrupt handler
void sys_tick_handler(void)
{
    milliseconds++;
}

void systick_init(uint32_t cpu_frequency)
{
    // Configure SysTick to trigger an interrupt every 1 ms
    systick_set_reload(cpu_frequency / 1000 - 1); // 1ms period
    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB); // Use CPU clock (AHB)
    systick_counter_enable();
    systick_interrupt_enable();
}

uint32_t millis(void)
{
    return milliseconds;
}

void delay_ms(uint32_t delay)
{
    uint32_t start = millis();
    while (millis() - start < delay) {
        // Busy wait
    }
}

////////////////////////////////////////////////////////////////////////////////////

void SysTick_Delay_1MS(__IO uint32_t c)
{
    SYSTICK->LOAD = SYSTICK_1MS_LOAD;
    SYSTICK->VAL = 0;
    SET(SYSTICK->CTL.CLKSRC);
    SET(SYSTICK->CTL.ENABLE);
    for (volatile uint32_t i = 0; i < c; i++)
    {
        SYSTICK->VAL = 0;
        while (NCHK(SYSTICK->CTL.COUNT));
    }
    CLR(SYSTICK->CTL.ENABLE);
}

void SysTick_Delay_1S(__IO uint32_t c)
{
    SYSTICK->LOAD = SYSTICK_1S_LOAD;
    SYSTICK->VAL = 0;
    SET(SYSTICK->CTL.CLKSRC);
    SET(SYSTICK->CTL.ENABLE);
    for (volatile uint32_t i = 0; i < c; i++)
    {
        SYSTICK->VAL = 0;
        while (NCHK(SYSTICK->CTL.COUNT));
    }
    CLR(SYSTICK->CTL.ENABLE);
}