#include "LCD.h"
#include <stdlib.h>

////////////////////////////////////////// Start of Functions //////////////////////////////////////////////////
//*************************************** New working Library *************************************************/
////////////////////////////////////////// Start of Functions //////////////////////////////////////////////////

void lcd_send_nibble(ST_LCD lcd,uint8_t nibble)
{
    GPIO_OUTPUT_LEVEL(lcd.D4, LOW);
    GPIO_OUTPUT_LEVEL(lcd.D5, LOW);
    GPIO_OUTPUT_LEVEL(lcd.D6, LOW);
    GPIO_OUTPUT_LEVEL(lcd.D7, LOW);

    if (nibble & 0x01) GPIO_OUTPUT_LEVEL(lcd.D4, HIGH);
    if (nibble & 0x02) GPIO_OUTPUT_LEVEL(lcd.D5, HIGH);
    if (nibble & 0x04) GPIO_OUTPUT_LEVEL(lcd.D6, HIGH);
    if (nibble & 0x08) GPIO_OUTPUT_LEVEL(lcd.D7, HIGH);

    GPIO_OUTPUT_LEVEL(lcd.EN, HIGH);
    SysTick_Delay_1MS(1); // Enable pulse
    GPIO_OUTPUT_LEVEL(lcd.EN, LOW);
    SysTick_Delay_1MS(1);
}

void lcd_send_byte(ST_LCD lcd, uint8_t data, uint8_t rs)
{
    if (rs) GPIO_OUTPUT_LEVEL(lcd.RS, HIGH); // Data mode
    else    GPIO_OUTPUT_LEVEL(lcd.RS, LOW);  // Command mode

    lcd_send_nibble(lcd, data >> 4);     // Send higher nibble
    lcd_send_nibble(lcd, data & 0x0F);   // Send lower nibble
}

void lcd_command(ST_LCD lcd, uint8_t cmd)
{
    lcd_send_byte(lcd, cmd, 0);
    SysTick_Delay_1MS(2); // Allow time for the command to process
}

void lcd_data(ST_LCD lcd,uint8_t data)
{
    lcd_send_byte(lcd, data, 1);
}

void lcd_init(ST_LCD lcd)
{
    CONF_GPIO(lcd.RS, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_50MHZ});
    CONF_GPIO(lcd.EN, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_50MHZ});
    CONF_GPIO(lcd.D7, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_50MHZ});
    CONF_GPIO(lcd.D6, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_50MHZ});
    CONF_GPIO(lcd.D5, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_50MHZ});
    CONF_GPIO(lcd.D4, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_50MHZ});

    // Initialization sequence
    SysTick_Delay_1MS(15); // Wait for LCD to power up
    lcd_send_nibble(lcd, 0x03); // Function set: 8-bit mode
    SysTick_Delay_1MS(5);
    lcd_send_nibble(lcd, 0x03);
    SysTick_Delay_1MS(1);
    lcd_send_nibble(lcd, 0x03);
    lcd_send_nibble(lcd, 0x02); // Function set: 4-bit mode

    lcd_command(lcd, 0x28); // Function set: 4-bit mode, 2 lines, 5x8 dots
    lcd_command(lcd, 0x08); // Display off
    lcd_command(lcd, 0x01); // Clear display
    SysTick_Delay_1MS(2);
    lcd_command(lcd, 0x06); // Entry mode: Increment cursor, no shift
    lcd_command(lcd, 0x0C); // Display on, cursor off, blink off
}

void lcd_clear(ST_LCD lcd)
{
    lcd_command(lcd, 0x01); // Clear display
    SysTick_Delay_1MS(2);
}

void lcd_set_cursor(ST_LCD lcd,uint8_t col, uint8_t row)
{
    uint8_t address = col + (row ? 0x40 : 0x00);
    lcd_command(lcd, 0x80 | address); // Set DDRAM address
}

void lcd_print_String(ST_LCD lcd, const char *str)
{
    while (*str)
    {
        lcd_data(lcd, *str++);
    }
}
void lcd_print_Int(ST_LCD lcd, uint16_t Number)
{
    char buffer [33];
    itoa(Number,buffer,10);

    lcd_print_String(lcd, buffer);
}
//////////////////////////////////////////// End of Functions //////////////////////////////////////////////////
//*************************************** New working Library *************************************************/
//////////////////////////////////////////// End of Functions //////////////////////////////////////////////////


////////////////////////////////////////// Start of Functions //////////////////////////////////////////////////
//************************************* Old not working Library ***********************************************/
////////////////////////////////////////// Start of Functions //////////////////////////////////////////////////
void LCD_init(ST_LCD lcd)
{
    CONF_GPIO(lcd.RS, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    CONF_GPIO(lcd.EN, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    CONF_GPIO(lcd.D7, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    CONF_GPIO(lcd.D6, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    CONF_GPIO(lcd.D5, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    CONF_GPIO(lcd.D4, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
}
void LCD_start(ST_LCD lcd)
{
    LCD_setdatapins(lcd, 0X00);
    for (volatile int i = 1065244; i <= 0; i--)
        asm("NOP");

    LCD_sendcmd(lcd, 0x03);
    for (volatile int i = 5065244; i <= 0; i--)
        asm("NOP");

    LCD_sendcmd(lcd, 0x03);
    for (volatile int i = 10065244; i <= 0; i--)
        asm("NOP");

    LCD_sendcmd(lcd, 0x03);
    LCD_sendcmd(lcd, 0x02);
    LCD_sendcmd(lcd, 0x02);
    LCD_sendcmd(lcd, 0x08);
    LCD_sendcmd(lcd, 0x00);
    LCD_sendcmd(lcd, 0x0C);
    LCD_sendcmd(lcd, 0x00);
    LCD_sendcmd(lcd, 0x06);
}

void LCD_setdatapins(ST_LCD lcd, uint8_t data)
{
    GPIO_OUTPUT_LEVEL(lcd.D4, data&1);
    GPIO_OUTPUT_LEVEL(lcd.D5, (data&2)>>1);
    GPIO_OUTPUT_LEVEL(lcd.D6, (data&4)>>2);
    GPIO_OUTPUT_LEVEL(lcd.D7, (data&8)>>3);
}

void LCD_sendcmd(ST_LCD lcd, uint8_t cmd)
{
    GPIO_OUTPUT_LEVEL(lcd.RS, LOW);
    LCD_setdatapins(lcd,cmd);
    GPIO_OUTPUT_LEVEL(lcd.EN,HIGH);
    for (volatile uint16_t i = 0; i < 40000; i++)
    {
        asm("NOP");
    }
    GPIO_OUTPUT_LEVEL(lcd.EN, LOW);
    
}

void LCD_clrdisp(ST_LCD lcd)
{
    LCD_sendcmd(lcd, 0);
    LCD_sendcmd(lcd, 1);
}

void LCD_setcrsr(ST_LCD lcd, uint8_t x, uint8_t y)
{
    char temp = 0;
    if(y==1)
    {
        temp=0x80 + x-1;

    }
    else if(y==2)
    {
        temp=0xC0 + x-1;
    }
    LCD_sendcmd(lcd, temp>>4);
    LCD_sendcmd(lcd, temp);

}

void LCD_printchar(ST_LCD lcd, char c)
{
    GPIO_OUTPUT_LEVEL(lcd.RS, HIGH);
    LCD_setdatapins(lcd, c >> 4);
    GPIO_OUTPUT_LEVEL(lcd.EN, HIGH);
    for (volatile int i = 100000; i <= 0; i--)
    {
        asm("NOP");
    }
    GPIO_OUTPUT_LEVEL(lcd.EN, LOW);
    LCD_setdatapins(lcd, c);
    GPIO_OUTPUT_LEVEL(lcd.EN, HIGH);
    for (volatile int i = 100000; i <= 0; i--)
    {
        asm("NOP");
    }
    GPIO_OUTPUT_LEVEL(lcd.EN, LOW);
}

void LCD_printstring(ST_LCD lcd, char *s)
{
    for (volatile int i = 0; s[i] != '\0'; i++)
    {
        LCD_printchar(lcd, s[i]);
    }
}
//////////////////////////////////////////// End of Functions //////////////////////////////////////////////////
//************************************* Old not working Library ***********************************************/
//////////////////////////////////////////// End of Functions //////////////////////////////////////////////////