#ifndef _KEYPAD_H_
#define _KEYPAD_H_
#include"../../HAL/GPIO/gpio.h"



#define KPAD_COL_PIN0  11
#define KPAD_COL_PIN1  10
#define KPAD_COL_PIN2  1
#define KPAD_COL_PIN3  0

#define KPAD_ROW_PIN_0  4
#define KPAD_ROW_PIN_1  5
#define KPAD_ROW_PIN_2  6
#define KPAD_ROW_PIN_3  7
#define INVALID_KEY  -1


void keypadinit();
uint32_t getkeypressed();
uint8_t is_stable_keypress(uint8_t row, uint8_t col);








#endif