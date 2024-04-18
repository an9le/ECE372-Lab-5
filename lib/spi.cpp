// Author: Angel Perez
// Net ID: aperez104
// Date: 04/16/2024
//
// Description: 
//----------------------------------------------------------------------//

#include "spi.h"
#include <Arduino.h>
#include <avr/io.h>

// Stalls until flag is raised (bladee)
#define stall while (!(SPSR & (1 << SPIF)));

void initSPI() {

    // We are only writing, so MISO won't be initialized
    // Set MOSI, SCK, and SS pins to output
    DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2);

    // Set SS high initially
    PORTB |= (1 << PORTB0);

    // Enable SPI, MSTR, CPOL, CPHA
    // fosc / 128: SPR1 = 1, SPR0 = 1
    // ADXL345, CPOL = 1 CPHA = 1
    SPCR |= (1 << SPIE) | (1 << SPE) | (1 << MSTR) | (1 << CPOL) | (1 << CPHA) | (1 << SPR1) | (1 << SPR0);

    write(0x09, 0x00);          // Decoding：Binary Coded Decimal
    write(0x0A, 0x08);          // Brightness control
    write(0x0B, 0x07);          // Scan limit: 8 LEDs
    write(0x0C, 0x01);          // Power-down mode：0，normal mode：1
    write(0x0F, 0x00);          // Test Display

}



void write(unsigned char command, unsigned char data) {
    PORTB &= ~(1 << PORTB0);    // Enable chip select
    SPDR = command;             // Load the CMD address into register
    stall;                       
    SPDR = data;                // Load the data into register
    stall;                       
    PORTB |= (1 << PORTB0);     // Disable chip select
}



void frown() {
  write(0x01, 0b00000000);      // Row 1 LEDS
  write(0x02, 0b01100110);      // Row 2 LEDS
  write(0x03, 0b01100110);      // Row 3 LEDS
  write(0x04, 0b00000000);      // Row 4 LEDS
  write(0x05, 0b00000000);      // Row 5 LEDS
  write(0x06, 0b00111100);      // Row 6 LEDS
  write(0x07, 0b01000010);      // Row 7 LEDS
  write(0x08, 0b10000001);      // Row 8 LEDS
}



void smile() { 
  write(0x01, 0b00000000);      // Row 1 LEDS
  write(0x02, 0b01100110);      // Row 2 LEDS
  write(0x03, 0b01100110);      // Row 3 LEDS
  write(0x04, 0b00000000);      // Row 4 LEDS
  write(0x05, 0b00000000);      // Row 5 LEDS
  write(0x06, 0b10000001);      // Row 6 LEDS
  write(0x07, 0b01000010);      // Row 7 LEDS
  write(0x08, 0b00111100);      // Row 8 LEDS
}
