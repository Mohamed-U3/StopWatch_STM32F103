#ifndef _HBRIDGE_H
#define _HBRIDGE_H

#include "..\..\HAL\GPIO\gpio.h"

typedef struct{
    ST_PORT_PIN IN1;
    ST_PORT_PIN IN2;
    ST_PORT_PIN ENA;
    ST_PORT_PIN IN3;
    ST_PORT_PIN IN4;
    ST_PORT_PIN ENB;
}ST_HBD; 

typedef enum 
{
    FORWARD,
    BACKWARD
}EN_MOTOR_DIRECTION;

void HBD_init(ST_HBD Hbridge, uint8_t IS_PWM_USED);
void HBD_Direction(ST_HBD Hbridge, EN_MOTOR_DIRECTION DIR); 
void HBD_On(ST_HBD Hbridge, uint8_t IS_PWM_USED);
void HBD_Ctrl(ST_HBD Hbridge, EN_MOTOR_DIRECTION DIR, uint8_t IS_PWM_USED);

#endif