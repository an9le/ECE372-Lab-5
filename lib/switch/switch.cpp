#include <avr/io.h>
#include "switch.h"

void initSwitch(){
    // Using Data Direction Register to make PORTD2 an input
    DDRD &= ~(1 << PD2); 

    // Enable Pull-up resistor when using switches
    PORTD |= (1 << PORTD2); 

    // External Interrupt Mask Register
    EIFR |= (1 << INTF2); 
    
    // External Interrupt Flag Register
    EIMSK |= (1 << INT2); 
}
