#include "app.h"

// Operating modes
typedef enum
{
  STOPWATCH_MODE,
  COUNTDOWN_MODE
} OperatingMode;

// Timer states
typedef enum
{
  READY,
  RUNNING,
  PAUSED,
  SETTING // For countdown mode only
} TimerState;

ST_button b1 = {{EN_PORTB, 11}, Active_low}; // Start, Stop, Reset button
ST_button b2 = {{EN_PORTB, 10}, Active_low}; // Mode toggle and value adjustment button
ST_LCD lcd1 = {{EN_PORTA, 11}, {EN_PORTA, 8}, {EN_PORTB, 12}, {EN_PORTB, 13}, {EN_PORTB, 14}, {EN_PORTB, 15}};
ST_PORT_PIN RunningLED = {EN_PORTC, 13}; // LED for running indicator
ST_PORT_PIN StoppedLED = {EN_PORTB, 1};  // LED for stopped/zero indicator

// Global variables
static OperatingMode currentMode = STOPWATCH_MODE;
static TimerState currentState = READY;
static uint32_t startTime = 0;
static uint32_t pausedTime = 0;
static uint32_t elapsedTime = 0;
static uint32_t countdownValue = 60000; // Default 1 minute (in ms)
static uint32_t lastButtonPressTime = 0;
static uint8_t longPressCounter = 0;

void updateDisplay(uint32_t timeInMs, bool isCountdown)
{
  uint32_t total_seconds = timeInMs / 1000;
  uint32_t minutes = total_seconds / 60;
  uint32_t seconds = total_seconds % 60;
  uint32_t milliseconds = (timeInMs % 1000) / 10; // Show centiseconds

  // Update mode indication
  lcd_set_cursor(lcd1, 0, 0);
  lcd_print_String(lcd1, isCountdown ? "Countdown: " : "Stopwatch: ");

  // Update time display
  lcd_set_cursor(lcd1, 0, 1);
  lcd_print_Int(lcd1, minutes);
  lcd_print_String(lcd1, ":");
  if (seconds < 10)
    lcd_print_String(lcd1, "0");
  lcd_print_Int(lcd1, seconds);
  lcd_print_String(lcd1, ".");
  if (milliseconds < 10)
    lcd_print_String(lcd1, "0");
  lcd_print_Int(lcd1, milliseconds);
}

void handleModeToggle(void)
{
  if (currentState == READY)
  {
    currentMode = (currentMode == STOPWATCH_MODE) ? COUNTDOWN_MODE : STOPWATCH_MODE;
    if (currentMode == COUNTDOWN_MODE)
    {
      currentState = SETTING;
      elapsedTime = countdownValue;
    }
    else
    {
      elapsedTime = 0;
    }
  }
}

void handleCountdownAdjustment(void)
{
  if (currentState == SETTING)
  {
    if (button_pressed(b1))
    {
      countdownValue += 60000;      // Add 1 minute
      if (countdownValue > 3600000) // Max 1 hour
        countdownValue = 60000;
    }
    if (button_pressed(b2))
    {
      if (countdownValue > 60000)
        countdownValue -= 60000; // Subtract 1 minute
    }
    elapsedTime = countdownValue;
  }
}

void handleButton1Press(void)
{
  uint32_t currentTime = millis();

  // Debounce protection
  if (currentTime - lastButtonPressTime < 200)
  {
    return;
  }
  lastButtonPressTime = currentTime;

  switch (currentState)
  {
  case READY:
    if (currentMode == COUNTDOWN_MODE)
    {
      elapsedTime = countdownValue;
    }
    startTime = millis();
    currentState = RUNNING;
    break;

  case RUNNING:
    pausedTime = elapsedTime;
    currentState = PAUSED;
    break;

  case PAUSED:
    startTime = millis() - (currentMode == COUNTDOWN_MODE ? (countdownValue - pausedTime) : pausedTime);
    currentState = RUNNING;
    break;

  case SETTING:
    currentState = READY;
    elapsedTime = countdownValue;
    break;
  }
}

void checkLongPress(void)
{
  if (button_pressed(b1))
  {
    longPressCounter++;
    if (longPressCounter > 10) // About 3 seconds at typical loop speed
    {
      // Stop/Reset
      currentState = READY;
      startTime = 0;
      pausedTime = 0;
      elapsedTime = (currentMode == COUNTDOWN_MODE) ? countdownValue : 0;
      longPressCounter = 0;
    }
  }
  else
  {
    longPressCounter = 0;
  }
}

void updateLEDs(void)
{
  // Running LED
  GPIO_OUTPUT_LEVEL(RunningLED, (currentState == RUNNING) ? LOW : HIGH);

  // Stopped/Zero LED
  bool isZero = (currentMode == COUNTDOWN_MODE && elapsedTime == 0) ||
                (currentMode == STOPWATCH_MODE && currentState == READY);
  GPIO_OUTPUT_LEVEL(StoppedLED, isZero ? LOW : HIGH);
}

void APP_Init(void)
{
  lcd_init(lcd1);
  lcd_clear(lcd1);
  lcd_set_cursor(lcd1, 0, 0);
  lcd_print_String(lcd1, "Dual Mode Timer");
  SysTick_Delay_1S(2);
  systick_init(72000000);

  // Configure LEDs
  CONF_GPIO(RunningLED, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
  CONF_GPIO(StoppedLED, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});

  lcd_clear(lcd1);
}

void APP_Loop(void)
{
  static uint8_t lastButton1State = 0;
  static uint8_t lastButton2State = 0;
  uint8_t currentButton1State = button_pressed(b1);
  uint8_t currentButton2State = button_pressed(b2);

  // Handle mode toggle (Button 2)
  if (currentButton2State && !lastButton2State)
  {
    handleModeToggle();
  }

  // Handle main button (Button 1)
  if (currentButton1State && !lastButton1State)
  {
    handleButton1Press();
  }

  // Check for long press
  checkLongPress();

  // Handle countdown adjustment in SETTING state
  if (currentMode == COUNTDOWN_MODE && currentState == SETTING)
  {
    handleCountdownAdjustment();
  }

  // Update time
  if (currentState == RUNNING)
  {
    if (currentMode == STOPWATCH_MODE)
    {
      elapsedTime = millis() - startTime;
    }
    else // COUNTDOWN_MODE
    {
      uint32_t elapsed = millis() - startTime;
      if (elapsed >= countdownValue)
      {
        elapsedTime = 0;
        currentState = READY;
      }
      else
      {
        elapsedTime = countdownValue - elapsed;
      }
    }
  }

  // Update display and LEDs
  updateDisplay(elapsedTime, currentMode == COUNTDOWN_MODE);
  updateLEDs();

  lastButton1State = currentButton1State;
  lastButton2State = currentButton2State;
}

void APP_Start(void)
{
    APP_Init();
    while (1)
    {
        APP_Loop();
    }
}