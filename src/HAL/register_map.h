/*
This header file contains the registers physical address, extracted from STM32F103  both reference and programming manual.
*/
#ifndef __REGISTER_MAP_H__
#define __REGISTER_MAP_H__

#define PERIPH_BASE         (0x40000000UL)
#define CORE_PERIPH_BASE    (0xE000E000UL)

#define SYSTICK_OFFSET      (0x10)
#define SYSTICK_BASE        (CORE_PERIPH_BASE+SYSTICK_OFFSET)

#define GPIO_A_OFFSET   (0x10800UL)
#define GPIO_A_BASE     (PERIPH_BASE+GPIO_A_OFFSET)

#define GPIO_B_OFFSET   (0x10C00UL)
#define GPIO_B_BASE     (PERIPH_BASE+GPIO_B_OFFSET)

#define GPIO_C_OFFSET   (0x11000UL)
#define GPIO_C_BASE     (PERIPH_BASE+GPIO_C_OFFSET)

#define GPIO_D_OFFSET   (0x11400UL)
#define GPIO_D_BASE     (PERIPH_BASE+GPIO_D_OFFSET)

#define RCC_OFFSET            (0x21000UL)
#define RCC_BASE              (PERIPH_BASE+RCC_OFFSET)

#define TIM2_OFFSET           (0X0UL)
#define TIM2_BASE           (PERIPH_BASE+TIM2_OFFSET)


#define TIM3_OFFSET           (0X400UL)
#define TIM3_BASE           (PERIPH_BASE+TIM3_OFFSET)

#define TIM4_OFFSET           (0X800UL)
#define TIM4_BASE           (PERIPH_BASE+TIM4_OFFSET)

#define TIM5_OFFSET           (0X0UL)
#define TIM5_BASE           (PERIPH_BASE+TIM5_OFFSET)

#define ADC1_OFFSET          (0x12400UL)
#define ADC1_BASE             (PERIPH_BASE+ADC1_OFFSET)
#endif