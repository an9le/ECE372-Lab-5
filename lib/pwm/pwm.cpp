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

const int sys_clk = 16000000;

void initPWMTimer3() {
    // Open PE3 as Output
    DDRE |= (1 << DDE3);

    // Set Timer 3 to PWM mode 15 (Up to TOP:ICR3) [1111]
    TCCR3A |= (1 << WGM30) | (1 << WGM31); // COM3A1 Controls Output Compare
    TCCR3B |= (1 << WGM32) | (1 << WGM33);

    // Non-Inverting Mode [10]
    TCCR3A &= ~(1 << COM3C0);
    TCCR3A |=  (1 << COM3C1);

    // Set Prescaler to 1 [001]
    TCCR3B |= (1 << CS30);
}

// Chirping Sound Should go From 1 kHz to 4 kHz
void changeFrequency(int frequency) {
    int top_value = sys_clk / frequency; // Calculated Value for 'TOP'
    OCR3A = top_value;
}

void chirp() {
    for (int frequency = 1000; frequency <= 4000; frequency++)
    {
        changeFrequency(frequency);
    }
}

// void alarmOn() { }

// void alarmOff() { }

// Description:
//          Changes the duty cycle of the PWM signal according to 10-bit ADC Values
// Input:
//          Right-Handed ADC_H and ADC_L -> `duty = (ADC_H << 8) | ADC_L`
// void changeDutyCycle(uint16_t duty) {
//     float duty_cycle; // Float Value for calculation

//     // Checks if we are at ~2.5V
//     if(duty == 512) {
//         duty_cycle = 0;
//     }
//     // Calculation if Running Above 2.5V (Adjusted to Max at 1023)
//     else if(duty > 512) {
//         duty_cycle = ((duty + 1) - 512) / 512.0;
//     }
//     // Calculation if Running Below 2.5V (Adjusted to Max at 0)
//     else if(duty < 512)
//     {
//         duty_cycle = (512 - duty) / 512.0;
//     }

//     OCR3A = (int) (duty_cycle * top_value); // Calulates OCRnA value and Casts to type int
// }