#ifndef __ADC_H__
#define __ADC_H__
#include "../../HAL/GPIO/gpio.h"
#include"../../HAL/register.h"
#include"../../HAL/register_map.h"
#include"../../HAL/systick/systick.h"



void adc_INIT(void);

uint32_t adc_READ(uint8_t channel);





#endif