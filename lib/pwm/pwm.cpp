// Author: Alek Sepulveda
// Net ID: aleksepulveda
// Date: 04/17/2024
// Assignment: Lab 5
//
// Description: Use Timer3 to generate a PWM signal
//              for controlling a piezo buzzer/speaker, implements a
//                  `changeFrequency()`
//              function for controlling the piezo sound
//----------------------------------------------------------------------//
#include <avr/io.h>
#include "pwm.h"
#include <timer.h>

void initPWMTimer3() {
    // Open PE4 as Output
    DDRE |= (1 << DDE4);

    // Set Timer 3 to PWM mode 15 (Up to TOP:ICR3) [1111]
    TCCR3A |= (1 << WGM30) | (1 << WGM31); // COM3A1 Controls Output Compare
    TCCR3B |= (1 << WGM32) | (1 << WGM33);

    // Non-Inverting Mode [10]
    TCCR3A &= ~(1 << COM3B0);
    TCCR3A |=  (1 << COM3B1);

    // Set Prescaler to 1 [001]
    TCCR3B |= (1 << CS30);
}

// Chirping Sound Should go From 1 kHz to 4 kHz
void changeFrequency(int frequency) {
    int top_value = 16000000 / frequency; // Calculated Value for 'TOP'

    // 16000000
    OCR3A = top_value;
    OCR3AH = OCR3A >> 8;
    OCR3AL = OCR3A;
    OCR3BH = OCR3AH >> 1;
    OCR3BL = OCR3AL >> 1;
}

void chirp() {
    for (int frequency = 1000; frequency <= 4000; frequency++)
    {
        changeFrequency(frequency);
    }
}

void alarmOn() { 
    TCCR3B |= (1 << CS30);
}

void alarmOff() { 
    TCCR3B &= ~(1 << CS30);
}
