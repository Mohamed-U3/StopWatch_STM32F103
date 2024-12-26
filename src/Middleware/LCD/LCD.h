#ifndef __LCD_HH__
#define __LCD_HH__
#include"../../HAL/GPIO/gpio.h"
#include"../../HAL/SYSTICK/systick.h"

typedef struct LCD
{
    ST_PORT_PIN RS;
    ST_PORT_PIN EN;
    ST_PORT_PIN D4;
    ST_PORT_PIN D5;
    ST_PORT_PIN D6;
    ST_PORT_PIN D7;
    
} ST_LCD;

void LCD_init(ST_LCD lcd);
void LCD_start(ST_LCD lcd);

void LCD_setdatapins(ST_LCD lcd, uint8_t data);
void LCD_sendcmd(ST_LCD lcd, uint8_t cmd);

void LCD_clrdisp(ST_LCD lcd );
void LCD_setcrsr(ST_LCD lcd, uint8_t x, uint8_t y);

void LCD_printchar(ST_LCD lcd, char c);
void LCD_printstring(ST_LCD lcd, char* s);

//U3 edit
void lcd_send_nibble    (ST_LCD lcd, uint8_t nibble             );
void lcd_send_byte      (ST_LCD lcd, uint8_t data, uint8_t rs   );
void lcd_command        (ST_LCD lcd, uint8_t cmd                );
void lcd_data           (ST_LCD lcd, uint8_t data               );
void lcd_init           (ST_LCD lcd                             );
void lcd_clear          (ST_LCD lcd                             );
void lcd_set_cursor     (ST_LCD lcd, uint8_t col,  uint8_t row  );
void lcd_print_String   (ST_LCD lcd, const char *str            );
void lcd_print_Int      (ST_LCD lcd, uint16_t Number            );

#endif