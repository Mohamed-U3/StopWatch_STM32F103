#ifndef TIMER_H
#define TIMER_H

#include "../register.h"
#include "../GPIO/gpio.h"

typedef enum {
    TIMER2,
    TIMER3,
    TIMER4,
    TIMER5
} EN_TIMERx;

typedef enum {
    TIMER_MODE_UP,      // Count up
    TIMER_MODE_DOWN     // Count down
} EN_TimerMode_t;

typedef struct {
    EN_TIMERx TIMER;         // Timer instance (e.g., TIM2, TIM3)
    uint32_t Prescalar;      // Prescaler value
    uint32_t Period;         // Auto-reload value
    EN_TimerMode_t Mode;     // Timer mode
} TimerConfig_t;

// Function prototypes
EN_IO_STAT_t SET_RCCTIM(EN_TIMERx TIMER);
TIM_Typedef* GET_TIMER_REG(EN_TIMERx TIMER);

EN_IO_STAT_t TIMER_INIT(TimerConfig_t *config);
void TIMER_START(EN_TIMERx TIMER);
void TIMER_STOP(EN_TIMERx TIMER);
void TIMER_SET_PERIOD(EN_TIMERx TIMER, uint32_t period);
void TIMER_WAIT_UNTIL_FINISHED(EN_TIMERx TIMER);


#endif // TIMER_H