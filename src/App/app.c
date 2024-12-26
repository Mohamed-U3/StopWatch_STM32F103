#include "app.h"

ST_button b1={{EN_PORTB,11},Active_low};  //First push botton for (Start, Stop, and reset).
ST_button b2={{EN_PORTB,10},Active_low};  //Second Push Botton for toggling the modes.
ST_LCD lcd1={{EN_PORTA, 11},{EN_PORTA, 8},{EN_PORTB, 12},{EN_PORTB,13},{EN_PORTB,14}, {EN_PORTB, 15}}; // LCD pins
ST_PORT_PIN BuiltinPin = {EN_PORTC, 13}; // Built-in LED pin

void updateDisplay(uint32_t ms, uint32_t sec, uint32_t min); // Function prototype

// Function to update the LCD display
void updateDisplay(uint32_t ms, uint32_t sec, uint32_t min)
{
  static uint32_t _min = 0;
  static uint32_t _sec = 0;
  static uint32_t _ms = 0;

  if (_min != min)
  {
    _min = min;
    lcd_set_cursor(lcd1, 0, 1); // First row and 7th column of the LCD
    lcd_print_Int(lcd1, min);
    lcd_print_String(lcd1, "min");
  }
  else if (min == 0)
  {
    lcd_set_cursor(lcd1, 0, 1); // First row and 7th column of the LCD
    lcd_print_Int(lcd1, min);
    lcd_print_String(lcd1, "min");
  }

  if (_sec != sec)
  {
    _sec = sec;
    lcd_set_cursor(lcd1, 6, 1); // First row and 7th column of the LCD
    lcd_print_Int(lcd1, sec);
    lcd_print_String(lcd1, "s ");
  }
  else if (sec == 0)
  {
    lcd_set_cursor(lcd1, 6, 1); // First row and 7th column of the LCD
    lcd_print_Int(lcd1, sec);
    lcd_print_String(lcd1, "s ");
  }

  if (_ms != ms)
  {
    _ms = ms;
    lcd_set_cursor(lcd1, 11, 1); // Second row of the LCD
    lcd_print_Int(lcd1, ms);
    lcd_print_String(lcd1, "0ms");
  }
}

void APP_Init(void)
{
  lcd_init(lcd1);               // Initialize the LCD
  lcd_clear(lcd1);              // Clear the LCD
  lcd_set_cursor(lcd1,0, 0);     // Set cursor to first row, first column
  lcd_print_String(lcd1, "Stopwatch App"); // Display message
  SysTick_Delay_1S(2);          // Delay 2 seconds
  systick_init(72000000); // CPU frequency in Hz (72 MHz for Blue Pill)

  lcd_clear(lcd1);
  lcd_print_String(lcd1, "Time: ");
  CONF_GPIO(BuiltinPin, (ST_PORT_PIN_CONF){OUTPUT,GEN_OUT_PUSH,OUT_SPEED_10MHZ}); // Configure the built-in LED pin as output
}

uint32_t time_s = 0;
uint32_t time_ms = 0;
uint32_t time_M = 0;
void APP_Loop(void)
{
  // GPIO_OUTPUT_LEVEL(BuiltinPin, LOW);
  // SysTick_Delay_1S(1);
  // GPIO_OUTPUT_LEVEL(BuiltinPin, HIGH);
  // SysTick_Delay_1S(1);
  // Delay(1000);
  // SysTick_Delay_1MS(1000-180); // Delay 1 Second (1000ms - Consumed time by other functions)

  if(button_pressed(b1) || button_pressed(b2))
  {
    GPIO_OUTPUT_LEVEL(BuiltinPin, HIGH); // Turn off the LED
  }
  else
  {
    GPIO_OUTPUT_LEVEL(BuiltinPin, LOW); // Turn on the LED
  }

  time_M = millis()/1000/60;
  time_s = millis()/1000- time_M*60;
  time_ms = millis() - time_s*1000 - time_M*60*1000;
  updateDisplay(time_ms/10, time_s, time_M);
}

void APP_Start(void)
{
  APP_Init();

  while (1)
  {
    APP_Loop();
  }
}