#include "keypad.h"
uint8_t KPAD_MATRIX[4][4]=
{
		{'H','A','S','N'},
		{'4','5','6','r'},
		{'1','2','3','h'},
		{'s','0','n','a'}
};
uint8_t col_arr[4] = {KPAD_COL_PIN0,KPAD_COL_PIN1,KPAD_COL_PIN2,KPAD_COL_PIN3};
uint8_t row_arr[4] = {KPAD_ROW_PIN_0,KPAD_ROW_PIN_1,KPAD_ROW_PIN_2,KPAD_ROW_PIN_3};

void keypadinit()

{
    for(int i=0;i<4;i++)

    { 
        ST_PORT_PIN col={EN_PORTB,col_arr[i]};
        ST_PORT_PIN arr={EN_PORTA,row_arr[i]};
        CONF_GPIO(col,(ST_PORT_PIN_CONF){OUTPUT,GEN_OUT_PUSH,OUT_SPEED_10MHZ});
        CONF_GPIO(arr,(ST_PORT_PIN_CONF){INPUT,INPUT_FLOATING,OUT_SPEED_10MHZ});


    }
}

// Function to check if the key press is stable
uint8_t is_stable_keypress(uint8_t row, uint8_t col) {
    for (int i = 0; i < 4; i++) {  // Sample the row pin 3 times
        if (GPIO_INPUT_READ((ST_PORT_PIN){EN_PORTA, row}) != 0) 
        {
            return 0;  // If HIGH detected, it's not a stable press
        }
        SysTick_Delay_1MS(50);  // Short delay between samples
    }
    return 1;  // Stable press detected
}

uint32_t getkeypressed() {
    uint32_t number = INVALID_KEY;  // Default to no key pressed
    uint8_t exit = 0;  // Flag to exit the loops
    EN_IO_LEVEL_t status;

    // Timeout mechanism to prevent indefinite blocking
    uint32_t timeout = 1000;  // Timeout in milliseconds

    for (int i = 0; i < 4; i++) {
        if (exit != 0 || timeout == 0) {  // Break if a key is pressed or timeout occurs
            break;
        }

        // Set current column LOW
        GPIO_OUTPUT_LEVEL((ST_PORT_PIN){EN_PORTB, col_arr[i]}, LOW);

        for (int j = 0; j < 4; j++) {
            // Read the row pin state
            status = GPIO_INPUT_READ((ST_PORT_PIN){EN_PORTA, row_arr[j]});

            // Check for key press
            if (status == 0 && is_stable_keypress(row_arr[j], col_arr[i])) {  // Key press detected and stable
                // Wait for the key to be released
                while (GPIO_INPUT_READ((ST_PORT_PIN){EN_PORTA, row_arr[j]}) == 0);

                // Map the key press to its corresponding number
                number = KPAD_MATRIX[j][i];
                exit = 1;  // Exit both loops
                break;
            }
        }

        // Reset the current column HIGH
        GPIO_OUTPUT_LEVEL((ST_PORT_PIN){EN_PORTB, col_arr[i]}, HIGH);

        timeout--;  // Decrement timeout counter
    }

    return number;  // Return the detected key or INVALID_KEY
}