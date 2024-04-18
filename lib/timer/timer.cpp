// Author: Juan Campista
// Net ID: jfcampista
// Date: 04/16/2024
// Assignment: Lab 5
//
// Description: Initializing Timer1 , also incorperating delay method
//                
//                  `
//              
//----------------------------------------------------------------------//

#include <avr/io.h>
#include "timer.h"

void initTimer1() {
  //disables waveform
  TCCR1A &= ~(1 << WGM10);     
  TCCR1A &= ~(1 << WGM11);

  //enables waveform
  TCCR1B |= (1 << WGM12);       
  TCCR1B &= ~(1 << WGM13);      
}

void delayMs(unsigned int delay) {
    unsigned int count = 0;

    // prescaler = 64
    TCCR1B |= (1 << CS10) | (1 << CS11);
    TCCR1B &= ~(1 << CS12);

    while (count < delay) {         
        TIFR1 |= (1 << OCF1A);
        TCNT1 = 0;

        while (! (TIFR1 & (1 << OCF1A)));

        count++;
    }
    
    // time elapsed has been 1ms * delay after exiting
    // turns off clock
    TCCR1B &= ~((1 << CS10) | (1 << CS11));
    TCCR1B &= ~(1 << CS12);
}
