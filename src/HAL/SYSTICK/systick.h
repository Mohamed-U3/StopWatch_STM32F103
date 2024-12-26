#ifndef SYSTICK_H
#define SYSTICK_H
#include "../../Common/bitop.h"
#include "../register.h"
#include <libopencm3/cm3/systick.h>
#pragma GCC optimize "O0"

#define SYS_CLK 9000000   //for 72MHz CPU (By default, the SysTick timer uses the AHB clock (core clock) divided by 8. - HCLK = 72 MHz then <72MHz/8 = 9MHz>)
#define SYSTICK_1MS_LOAD ((SYS_CLK / 1000) - 1)
#define SYSTICK_1S_LOAD (SYS_CLK - 1)

typedef struct
{
    uint32_t ENABLE : 1;
    uint32_t INTEN : 1;
    uint32_t CLKSRC : 1;
    uint32_t : 13;
    uint32_t COUNT : 1;
    uint32_t : 15;
} SYSTICK_TYPEDEF_CTL;

typedef struct
{
    __IO SYSTICK_TYPEDEF_CTL CTL;
    __IO uint32_t LOAD;
    __IO uint32_t VAL;
} SYSTICK_TYPEDEF;

#define SYSTICK ((SYSTICK_TYPEDEF *)SYSTICK_BASE)

void SysTick_Delay_1MS(volatile uint32_t c);
void SysTick_Delay_1S(volatile uint32_t c);

// U3 Edit - Function to return elapsed time in milliseconds
void systick_init(uint32_t cpu_frequency);      // Initializes the SysTick timer
uint32_t millis(void);                          // Returns the elapsed time in milliseconds since the program started
void delay_ms(uint32_t delay);                  // Delays the program for a specified number of milliseconds

#endif