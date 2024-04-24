// Author: Angel Perez, Juan Campista, Alek Sepulveda, and Brian Flores
// Net ID: aperez104
// Date: April 17th, 2024
// Assignment: Lab 5
//
// Description: The shell piecing all parts together
/*
    Requirements:
    - [X] pwm
    - [ ] i2c (Accelerometer)
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
#define POWER_CTRL 0x6B
#define WAKE    0x00
#define X_LOW   0x3C
#define X_HIGH  0x3B
#define Y_LOW   0x3E
#define Y_HIGH  0x3D
#define Z_LOW   0x40
#define Z_HIGH  0x3F

// Define a set of states that can be used in the state machine using an enum.
typedef enum switchStates {
    waitPress,
    debouncePress,
    waitRelease,
    debounceRelease
} button;

// Initialize state
volatile button button_state = waitPress;

typedef enum sysStates {
    quiet_smile,
    quiet_frown,
    alarm_smile,
    alarm_frown
} face;

// Initialize state
volatile face face_state = quiet_smile;

// Define Check to avoid 
bool tilt_check(int xPos, int zPos){};

int main(void) {

    sei();
    initTimer1();
    initPWMTimer3();
    initSPI();

    StartI2C_Trans(ADDRESS);
    write(POWER_CTRL);
    write(WAKE);

    Serial.begin(9600);

    // Declare Position Vars
    int xPos;
    int yPos;
    int zPos;

    while(1) {
        xPos = Read_data();
        yPos = Read_data();
        zPos = Read_data();

        Read_from(ADDRESS, X_HIGH);
        Read_from(ADDRESS, X_LOW);
        Read_from(ADDRESS, Y_HIGH);
        Read_from(ADDRESS, Y_LOW);
        Read_from(ADDRESS, Z_HIGH);
        Read_from(ADDRESS, Z_LOW);

        xPos = ((xPos << 8) | Read_data());
        yPos = ((yPos << 8) | Read_data());
        zPos = ((zPos << 8) | Read_data());

        // Control Logic
        // - Transitions States with Respect to Tilt
        switch (face_state) {
            case quiet_smile:
                alarmOff();
                smile();

                if (tilt_check(xPos, zPos)) face_state = alarm_frown;
                break;
            //----------------
            //----------------
            case alarm_frown:
                alarmOn();
                frown();
                chirp();

                if(not tilt_check(xPos, zPos)) face_state = alarm_smile;
                break;
            //----------------
            //----------------
            case quiet_frown:
                alarmOff();
                frown();

                if(not tilt_check(xPos, zPos)) face_state = quiet_smile;
                break;
            //----------------
            //----------------
            case alarm_smile:
                alarmOn();
                smile();
                chirp();

                if(tilt_check(xPos,zPos)) face_state = alarm_frown;
                break;
            //----------------
            //----------------
            default:
                break;
        }
    }
    return 0;
}

bool tilt_check(int xPos, int zPos) {
    if ((xPos >= 8000) || (xPos <= -8000) || (zPos >= 13000))
    {
        return true;
    }
    false;
}

// Function called when the button is pressed, i.e signal input from PORTD2
ISR(INT2_vect) { 

    // Normal State
    if(button_state == waitPress) {

        if (!(PIND & (1 << PD2))) {
            switch (face_state)
            {
                case alarm_frown:
                    face_state = quiet_frown;
                    break;
                //----------------
                //----------------
                case alarm_smile:
                    face_state = quiet_smile;
                    break;
                //----------------
                //----------------
                default:
                    break;
            }
            button_state = debouncePress;
        }

        else button_state = waitPress;
    }

    // Wait for Release
    else if(button_state == waitRelease) {

        if (PIND & (1 << PD2)) button_state = debounceRelease;

    }
}