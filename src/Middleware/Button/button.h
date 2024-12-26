#ifndef __BUTTON_H__
#define __BUTTON_H__
#include"../../HAL/GPIO/gpio.h"
#include<stdbool.h>
typedef enum
{
    Active_low,
    Active_high
} EN_BUTTON_ACTIVE_STATE_t;

typedef struct
{
    ST_PORT_PIN port_pin;
    EN_BUTTON_ACTIVE_STATE_t activestate;
} ST_button;

typedef enum
{
    BUTTON_ACTIVE,
    BUTTON_INACTIVE
} EN_BUTTON_STATE;

void button_init(ST_button b1);
bool button_pressed(ST_button b1);
EN_BUTTON_STATE buttonn_get_state(ST_button b1);

#endif