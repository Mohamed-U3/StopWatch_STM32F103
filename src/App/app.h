#ifndef __APP_H__
#define __APP_H__
#include "../Middleware/LED/led.h"
#include "../Middleware/LCD/LCD.h"
#include"../Middleware/SS/ss.h"
#include "../Middleware/Button/button.h"
#include "../HAL/SYSTICK/systick.h"
#include"../HAL/TIMER/timer.h"
#include "../Middleware/Hbridge/bridge.h"
#include "../HAL/ADC/adc.h"
void APP_Init(void);
void APP_Loop(void);
void APP_Start(void);

#endif