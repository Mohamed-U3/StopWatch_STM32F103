#include "adc.h"

void adc_INIT()
{
    RCC->RCC_APB2ENR |= (1<<9);     // enable ADC1 clock
    PORTA->GPIO_CRL = 0x44444440;   //set A0 as analog input
    ADC1->ADC_CR2 = 1;      /* ADON = 1 (power-up) */
    ADC1->ADC_SMPR2 = 7;    /* SMP1 = 001 (set sample time for IN1 to 7.5 clocks) */
    /// 1us delay
    volatile int i = 0;
    for (i = 0; i < 24; i++)    // 24 iterations for ~1 us at 72 MHz
        {
             __asm("NOP");      // Assembly instruction for "No Operation" (1 cycle)
        }
    /////////
}

uint32_t adc_READ(uint8_t channel)
{
    ADC1->ADC_SQR3 = channel;
    ADC1->ADC_CR2 = 1;
    while((ADC1->ADC_SR&(1<<1)) == 0);
    return ADC1->ADC_DR;
}
