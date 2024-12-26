#include "bridge.h"



void HBD_init(ST_HBD Hbridge, uint8_t IF_PWM_USED)
{
    if(IF_PWM_USED == 1)
    {
        CONF_GPIO(Hbridge.ENA, (ST_PORT_PIN_CONF){OUTPUT,GEN_OUT_PUSH,OUT_SPEED_10MHZ});   
        CONF_GPIO(Hbridge.ENB, (ST_PORT_PIN_CONF){OUTPUT,GEN_OUT_PUSH,OUT_SPEED_10MHZ});

    }
    else
    {
        CONF_GPIO(Hbridge.ENA, (ST_PORT_PIN_CONF){OUTPUT,GEN_OUT_PUSH,OUT_SPEED_10MHZ});
        CONF_GPIO(Hbridge.ENB, (ST_PORT_PIN_CONF){OUTPUT,GEN_OUT_PUSH,OUT_SPEED_10MHZ});

    }
    CONF_GPIO(Hbridge.IN1, (ST_PORT_PIN_CONF){OUTPUT,GEN_OUT_PUSH,OUT_SPEED_10MHZ});
    CONF_GPIO(Hbridge.IN2, (ST_PORT_PIN_CONF){OUTPUT,GEN_OUT_PUSH,OUT_SPEED_10MHZ});
    CONF_GPIO(Hbridge.IN3, (ST_PORT_PIN_CONF){OUTPUT,GEN_OUT_PUSH,OUT_SPEED_10MHZ});
    CONF_GPIO(Hbridge.IN4, (ST_PORT_PIN_CONF){OUTPUT,GEN_OUT_PUSH,OUT_SPEED_10MHZ});
}

void HBD_Direction(ST_HBD Hbridge, EN_MOTOR_DIRECTION DIR)
{
    if(DIR == FORWARD)
    {
        GPIO_OUTPUT_LEVEL(Hbridge.IN1, HIGH);
        GPIO_OUTPUT_LEVEL(Hbridge.IN2, LOW);
    }
    else if ( DIR == BACKWARD)
    {
        GPIO_OUTPUT_LEVEL(Hbridge.IN1, LOW);
        GPIO_OUTPUT_LEVEL(Hbridge.IN2, HIGH);
    }
} 

void HBD_On(ST_HBD Hbridge, uint8_t IS_PWM_USED)
{
    if(IS_PWM_USED != 1)
    GPIO_OUTPUT_LEVEL(Hbridge.ENA, HIGH);
}

void HBD_Ctrl(ST_HBD Hbridge, EN_MOTOR_DIRECTION DIR, uint8_t IS_PWM_USED)
{
    if(IS_PWM_USED != 1)
    {
        HBD_On(Hbridge,IS_PWM_USED);
    }
    HBD_Direction(Hbridge, DIR);
}