// Author: Angel Perez, Juan Campista, Alek Sepulveda, and Brian Flores
// Net ID: aperez104
// Date: April 17th, 2024
// Assignment: Lab 5
//
// Description: The shell piecing all parts together
/*
  Requirements:
    - [X] pwm
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
} button;

// Initialize state
volatile button button_state = waitPress;

// Variables 
volatile char count = 0;
volatile int result = 0;

// TODO:
// - [ ] Check Angle of Accellerometer
//    - [ ] (if >  45 degrees) -> Frown & Alarm
//    - [ ] (if <= 45 degrees) -> Smile & No Alarm
// - [ ] Button Interrupt Stops Alarm (Until we get back to smile)
int main(void) {

    sei(); // Enable global interrupts
    initTimer1();
    initPWMTimer3();
    initSPI();
    initSwitch();
    initI2C();

    // SLA Register address for configuring measurement mode
    StartI2C_Trans(ADDRESS);
    write(POWER_CTRL);
    write(WAKE);

    // while loop
    while(1) {

      int xPos = Read_data();
      int yPos = Read_data();
      int zPos = Read_data();


      Read_from(ADDRESS, X_HIGH);
      Read_from(ADDRESS, X_LOW);
      Read_from(ADDRESS, Y_HIGH);
      Read_from(ADDRESS, Y_LOW);
      Read_from(ADDRESS, Z_HIGH);
      Read_from(ADDRESS, Z_LOW);

      xPos = ((xPos << 8) | Read_data());
      yPos = ((yPos << 8) | Read_data());
      zPos = ((zPos << 8) | Read_data());

      if ((xPos >= 8000) || (xPos <= -8000) || (zPos <= 13000)) {
        frown();
        chirp();
      }
      else {
        smile();
      }

      switch(button_state) {
        case debouncePress:
          delayMs(1);
          button_state = waitRelease;
        break;

        case debounceRelease:
          delayMs(1);
          button_state = waitPress;
        break;

        default:
        break;
      }
    }

return 0;
}


// Function called when the button is pressed, i.e signal input from PORTD2
ISR(INT2_vect) { 

  // Normal State
  if(button_state == waitPress) {
    chirp();
    button_state = debouncePress;
  }

  // Wait
  else if(button_state == waitRelease) {
    button_state = debounceRelease;
  }

}
