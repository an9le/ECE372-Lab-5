// Author: Brian Flores
// Net ID: brianflores
// Date: 04/16/2024
// Assignment: Lab 5
//
//  It defines functions to initialize the I2C hardware, start and stop I2C transactions, write to, and read from an I2C device based on the instructions given.
//                  `
//              
//----------------------------------------------------------------------//
#include "i2c.h"
#include <avr/io.h>
#include "Arduino.h"

#define wait_for_completion while(!(TWCR & (1 << TWINT))) // waits until the I2C hardware has completed an operation
#define WRITE_BIT 0
#define READ_BIT 1

//Function to initialize the I2C hardware
void initI2C() {
  PRR0 &= ~(1<<PRTWI);  // wake up I2C module on AT2560 power management register, disables power reduction mode
  
  TWSR |= (1 << TWPS0);
  TWSR &= ~(1 << TWPS1);  // Sets prescaler to 1

  //TWBR=((CPU Clock frequency)/(SCL frequency)-16)/(2*(4)^TWPS)
  TWBR = 0xC6; // bit rate generator = 200kHz  (TWBR = 32), settting the interface bit rate register TWBR

  TWCR |= (1 << TWINT ) | (1 << TWEN); // enables two wire interface and clears the interrupt flag

}

// Function to start an I2C transmission
void StartI2C_Trans(unsigned char SLA) {

// this function initiates a start condition and calls slave device with SLA plus write bit
//unsigned int stat;

  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // clear TWINT, intiate a start condition and enable
  wait_for_completion; //waits for the operation to complete
  
  TWDR = (SLA << 1); // slave address + write bit '0' for writing

  TWCR = ((1<<TWINT)| (1<<TWEN));  // trigger action:clear flag and enable I2C
  wait_for_completion;

}

void StopI2C_Trans() {
  // this function sends a stop condition to stop I2C transmission

  TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); //trigger action:  send stop condition

}
void write(unsigned char data){
  // this function loads the data passed into the I2C data register and transmits
  TWDR = data; //load data into TWDR (data) register
  TWCR = (1<<TWINT)|(1<<TWEN);  // trigger action:  clear flag and enable TWI (I2C)
  wait_for_completion;
}


// function that reads 6 bytes of accelerometer data
void Read_Acc(unsigned char SLA, unsigned char MEMADDRESS) {

  StartI2C_Trans(SLA); //Starts the I2C transaction
  write(MEMADDRESS);  // internal address to start read from.

  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // restarts to switch to read mode (repeated start condition)
  wait_for_completion;
 
  TWDR = (SLA << 1) | READ_BIT; // 7 bit address for slave plus read bit
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);// trigger, enabling acknowledgement
  wait_for_completion;

  TWCR = (1 << TWINT) | (1 << TWEN);// trigger with master sending ack
  wait_for_completion;
  
  StopI2C_Trans();
}

unsigned char read_Data(){
  return TWDR;    // returns the data from the data register
}
