#include "button.h"

void button_init(ST_button b1)
{
    CONF_GPIO(b1.port_pin, (ST_PORT_PIN_CONF){INPUT, INPUT_FLOATING, OUT_SPEED_10MHZ});
}

bool button_pressed(ST_button b1)
{
    if( GPIO_INPUT_READ(b1.port_pin)== b1.activestate)
    {
     return  true;   
    }
    return false;
}

EN_BUTTON_STATE buttonn_get_state(ST_button b1)
{
EN_IO_LEVEL_t val = GPIO_INPUT_READ(b1.port_pin);
if(val==HIGH&&b1.activestate==Active_high)
{return BUTTON_ACTIVE;

}else if(val==LOW&&b1.activestate==Active_low){return BUTTON_ACTIVE;}
return BUTTON_INACTIVE;
}
