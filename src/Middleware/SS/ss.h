#ifndef _SS_H_
#define _SS_H_
#include"../../HAL/GPIO/gpio.h"
typedef struct
{
ST_PORT_PIN A;
ST_PORT_PIN B;
ST_PORT_PIN C;
ST_PORT_PIN D;
ST_PORT_PIN E;
ST_PORT_PIN F;
ST_PORT_PIN G;
ST_PORT_PIN COM;
ST_PORT_PIN DOT;
}ST_SS_Segment;


void SevenSegment_DisplayDigit(ST_SS_Segment seg, uint16_t number);
void SevenSegment_Init(ST_SS_Segment ss);
void SevenSegment_UpdateDisplay(ST_SS_Segment SS1, ST_SS_Segment SS2, ST_SS_Segment SS3, uint16_t number, uint8_t dotPosition);
void SevenSegment_DisplayNumber(ST_SS_Segment SS1, ST_SS_Segment SS2, ST_SS_Segment SS3, uint16_t number, uint8_t dotPosition);
void Delay(uint32_t ms);











// void config_ss(SS_st sevensegment);
// void disp_ss(SS_st sevensegment,uint8_t x);
// void disp_num_ss(SS_st s1,SS_st s2,uint8_t x);
// void delay_ms(uint16_t milliseconds);
// void clear_ss(SS_st s);
// void stopwatch_ss(SS_st s1,SS_st s2,uint8_t time);
#endif