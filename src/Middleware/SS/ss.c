#include "SS.h"

void SevenSegment_Init(ST_SS_Segment SS)
{
    CONF_GPIO(SS.A, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    CONF_GPIO(SS.B, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    CONF_GPIO(SS.C, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    CONF_GPIO(SS.D, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    CONF_GPIO(SS.E, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    CONF_GPIO(SS.F, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    CONF_GPIO(SS.G, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    CONF_GPIO(SS.COM, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    CONF_GPIO(SS.DOT, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
}

void Delay(uint32_t ms)
{
    for (uint32_t i = 0; i < ms * 1100; i++)
    {
        __asm("nop");
    }
}

void SevenSegment_DisplayDigit(ST_SS_Segment seg, uint16_t number)
{
    switch (number)
    {
    case 0:
        GPIO_OUTPUT_LEVEL(seg.A, HIGH);
        GPIO_OUTPUT_LEVEL(seg.B, HIGH);
        GPIO_OUTPUT_LEVEL(seg.C, HIGH);
        GPIO_OUTPUT_LEVEL(seg.D, HIGH);
        GPIO_OUTPUT_LEVEL(seg.E, HIGH);
        GPIO_OUTPUT_LEVEL(seg.F, HIGH);
        GPIO_OUTPUT_LEVEL(seg.G, LOW);
        break;
    case 1:
        GPIO_OUTPUT_LEVEL(seg.A, LOW);
        GPIO_OUTPUT_LEVEL(seg.B, HIGH);
        GPIO_OUTPUT_LEVEL(seg.C, HIGH);
        GPIO_OUTPUT_LEVEL(seg.D, LOW);
        GPIO_OUTPUT_LEVEL(seg.E, LOW);
        GPIO_OUTPUT_LEVEL(seg.F, LOW);
        GPIO_OUTPUT_LEVEL(seg.G, LOW);
        break;
    case 2:
        GPIO_OUTPUT_LEVEL(seg.A, HIGH);
        GPIO_OUTPUT_LEVEL(seg.B, HIGH);
        GPIO_OUTPUT_LEVEL(seg.C, LOW);
        GPIO_OUTPUT_LEVEL(seg.D, HIGH);
        GPIO_OUTPUT_LEVEL(seg.E, HIGH);
        GPIO_OUTPUT_LEVEL(seg.F, LOW);
        GPIO_OUTPUT_LEVEL(seg.G, HIGH);
        break;
    case 3:
        GPIO_OUTPUT_LEVEL(seg.A, HIGH);
        GPIO_OUTPUT_LEVEL(seg.B, HIGH);
        GPIO_OUTPUT_LEVEL(seg.C, HIGH);
        GPIO_OUTPUT_LEVEL(seg.D, HIGH);
        GPIO_OUTPUT_LEVEL(seg.E, LOW);
        GPIO_OUTPUT_LEVEL(seg.F, LOW);
        GPIO_OUTPUT_LEVEL(seg.G, HIGH);
        break;
    case 4:
        GPIO_OUTPUT_LEVEL(seg.A, LOW);
        GPIO_OUTPUT_LEVEL(seg.B, HIGH);
        GPIO_OUTPUT_LEVEL(seg.C, HIGH);
        GPIO_OUTPUT_LEVEL(seg.D, LOW);
        GPIO_OUTPUT_LEVEL(seg.E, LOW);
        GPIO_OUTPUT_LEVEL(seg.F, HIGH);
        GPIO_OUTPUT_LEVEL(seg.G, HIGH);
        break;
    case 5:
        GPIO_OUTPUT_LEVEL(seg.A, HIGH);
        GPIO_OUTPUT_LEVEL(seg.B, LOW);
        GPIO_OUTPUT_LEVEL(seg.C, HIGH);
        GPIO_OUTPUT_LEVEL(seg.D, HIGH);
        GPIO_OUTPUT_LEVEL(seg.E, LOW);
        GPIO_OUTPUT_LEVEL(seg.F, HIGH);
        GPIO_OUTPUT_LEVEL(seg.G, HIGH);
        break;
    case 6:
        GPIO_OUTPUT_LEVEL(seg.A, HIGH);
        GPIO_OUTPUT_LEVEL(seg.B, LOW);
        GPIO_OUTPUT_LEVEL(seg.C, HIGH);
        GPIO_OUTPUT_LEVEL(seg.D, HIGH);
        GPIO_OUTPUT_LEVEL(seg.E, HIGH);
        GPIO_OUTPUT_LEVEL(seg.F, HIGH);
        GPIO_OUTPUT_LEVEL(seg.G, HIGH);
        break;
    case 7:
        GPIO_OUTPUT_LEVEL(seg.A, HIGH);
        GPIO_OUTPUT_LEVEL(seg.B, HIGH);
        GPIO_OUTPUT_LEVEL(seg.C, HIGH);
        GPIO_OUTPUT_LEVEL(seg.D, LOW);
        GPIO_OUTPUT_LEVEL(seg.E, LOW);
        GPIO_OUTPUT_LEVEL(seg.F, LOW);
        GPIO_OUTPUT_LEVEL(seg.G, LOW);
        break;
    case 8:
        GPIO_OUTPUT_LEVEL(seg.A, HIGH);
        GPIO_OUTPUT_LEVEL(seg.B, HIGH);
        GPIO_OUTPUT_LEVEL(seg.C, HIGH);
        GPIO_OUTPUT_LEVEL(seg.D, HIGH);
        GPIO_OUTPUT_LEVEL(seg.E, HIGH);
        GPIO_OUTPUT_LEVEL(seg.F, HIGH);
        GPIO_OUTPUT_LEVEL(seg.G, HIGH);
        break;
    case 9:
        GPIO_OUTPUT_LEVEL(seg.A, HIGH);
        GPIO_OUTPUT_LEVEL(seg.B, HIGH);
        GPIO_OUTPUT_LEVEL(seg.C, HIGH);
        GPIO_OUTPUT_LEVEL(seg.D, HIGH);
        GPIO_OUTPUT_LEVEL(seg.E, LOW);
        GPIO_OUTPUT_LEVEL(seg.F, HIGH);
        GPIO_OUTPUT_LEVEL(seg.G, HIGH);
        break;
    default:
        GPIO_OUTPUT_LEVEL(seg.A, LOW);
        GPIO_OUTPUT_LEVEL(seg.B, LOW);
        GPIO_OUTPUT_LEVEL(seg.C, LOW);
        GPIO_OUTPUT_LEVEL(seg.D, LOW);
        GPIO_OUTPUT_LEVEL(seg.E, LOW);
        GPIO_OUTPUT_LEVEL(seg.F, LOW);
        GPIO_OUTPUT_LEVEL(seg.G, LOW);
        break;
    }
}

void SevenSegment_UpdateDisplay(ST_SS_Segment SS1, ST_SS_Segment SS2, ST_SS_Segment SS3, uint16_t number, uint8_t dotPosition)
{
    static uint8_t current_seg = 0;
    uint16_t digit1 = number / 100;          // Extract hundreds place
    uint16_t digit2 = (number / 10) % 10;    // Extract tens place
    uint16_t digit3 = number % 10;           // Extract ones place

    ST_SS_Segment segments[3] = {SS1, SS2, SS3};
    uint16_t digits[3] = {digit1, digit2, digit3};

    // Turn off all COM pins and DOTs
    GPIO_OUTPUT_LEVEL(SS1.COM, LOW);
    GPIO_OUTPUT_LEVEL(SS2.COM, LOW);
    GPIO_OUTPUT_LEVEL(SS3.COM, LOW);
    GPIO_OUTPUT_LEVEL(SS1.DOT, LOW);
    GPIO_OUTPUT_LEVEL(SS2.DOT, LOW);
    GPIO_OUTPUT_LEVEL(SS3.DOT, LOW);

    // Handle leading zero suppression for the first digit
    if (current_seg == 0 && digit1 == 0)
    {
        // Skip displaying leading zero on the first digit
    }
    else
    {
        // Activate current segment and display the digit
        GPIO_OUTPUT_LEVEL(segments[current_seg].COM, HIGH);
        SevenSegment_DisplayDigit(segments[current_seg], digits[current_seg]);

        // Activate decimal point if the current segment matches the dot position
        if ((current_seg + 1) == dotPosition)
        {
            GPIO_OUTPUT_LEVEL(segments[current_seg].DOT, HIGH);
        }
    }

    // Update current segment for the next call
    current_seg = (current_seg + 1) % 3;
}

void SevenSegment_DisplayNumber(ST_SS_Segment SS1, ST_SS_Segment SS2, ST_SS_Segment SS3, uint16_t number, uint8_t dotPosition)
{
    while (1)
    {
        SevenSegment_UpdateDisplay(SS1, SS2, SS3, number, dotPosition);
        Delay(2); // Adjust the delay as needed for your display refresh rate
    }
}