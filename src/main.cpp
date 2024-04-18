// Author: Angel Perez, Juan Campista, Alek Sepulveda, and Brian Flores
// Net ID: aperez104
// Date: April 17th, 2024
// Assignment: Lab 5
//
// Description: The shell piecing all parts together
/*
// Requirements:
    - [] pwm
    - [] i2c (Accelerometer)
    - [X] spi (8x8 Matrix)
    - [X] switch
    - [X] timer
*/
//----------------------------------------------------------------------//

#include <Arduino.h>
#include <avr/io.h>
#include <timer.h>
#include <pwm.h>
#include <spi.h>
#include <switch.h>
#include <i2c.h>

// ADXL register addresses and configuration
#define ADDRESS 0x68  
#define POWER_CTRL 0x2D
#define WAKE    0x00
#define X_LOW   0x32
#define X_HIGH  0x33
#define Y_LOW   0x34
#define Y_HIGH  0x35
#define Z_LOW   0x36
#define Z_HIGH  0x37

// Define a set of states that can be used in the state machine using an enum.
typedef enum switchStates {
    waitPress,
    debouncePress,
    waitRelease,
    debounceRelease
} stateType;

// Initialize states.  Remember to use volatile 
volatile stateType state = waitPress;

// Variables 
volatile char count = 0;
volatile int result = 0;

int main(void) {

    sei(); // Enable global interrupts
    initTimer1();
    initPWMTimer3();
    initSPI();
    initSwitch();
    initI2C();

    Serial.begin(9600);
    Serial.flush();

    // SLA Register address for configuring measurement mode
    write(POWER_CTRL);
    write(WAKE);

    // while loop
    while(1) {

        switch(state) {
            case debouncePress:
                delayMs(1);
                state = waitRelease;
            break;

            case debounceRelease:
                delayMs(1);
                state = waitPress;
            break;

            default:
            break;
        }
    }

return 0;
}

/* Implement an Pin Change Interrupt which handles the switch being
* pressed and released. When the switch is pressed and released, the LEDs
* change at twice the original rate. If the LEDs are already changing at twice
* the original rate, it goes back to the original rate.
*/

// Function called when the button is pressed, i.e signal input from PORTD2
ISR(INT2_vect) { 

  // Normal State
  if(state == waitPress) {
    state = debouncePress;
  }

  // Wait
  else if(state == waitRelease) {
    state = debounceRelease;
  }

}
