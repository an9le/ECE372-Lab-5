#include "i2c.h"
#include <avr/io.h>
#include "Arduino.h"

#define wait_for_completion while(!(TWCR & (1 << TWINT)))
#define WRITE_BIT 0
#define READ_BIT 1


void initI2C() {
  PRR0 &= ~(1<<PRTWI);  // wake up I2C module on AT2560 power management register
  
  TWSR |= (1 << TWPS0);
  TWSR &= ~(1 << TWPS1);  // prescaler power = 1

  //TWBR=((CPU Clock frequency)/(SCL frequency)-16)/(2*(4)^TWPS)
  TWBR = 0xC6; // bit rate generator = 200kHz  (TWBR = 32)

  TWCR |= (1 << TWINT ) | (1 << TWEN); // enable two wire interface

}


void StartI2C_Trans(unsigned char SLA) {

// this function initiates a start condition and calls slave device with SLA plus write bit
//unsigned int stat;

  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // clear TWINT, intiate a start condition and enable
  wait_for_completion;
  
  TWDR = (SLA << 1); // slave address + write bit '0'

  TWCR = ((1<<TWINT)| (1<<TWEN));  // trigger action:clear flag and enable TWI
  wait_for_completion;

}

void StopI2C_Trans() {
  // this function sends a stop condition to stop I2C transmission

  TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); //trigger action:  send stop condition

}
void write(unsigned char data){
  // this function loads the data passed into the I2C data register and transmits
  TWDR = data; //load data into TWDR register
  TWCR = (1<<TWINT)|(1<<TWEN);  // trigger action:  clear flag and enable TWI
  wait_for_completion;
}


// function that reads 6 bytes of accelerometer data from ADXL345
// inputs are ADXL address and first register address for Xaxis low byte
//  returns pointer to static array
void Read_Acc(unsigned char SLA, unsigned char MEMADDRESS) {

  StartI2C_Trans(SLA);
  write(MEMADDRESS);  // internal address to start read from.

  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // restart to switch to read mode
  wait_for_completion;
 
  TWDR = (SLA << 1) | READ_BIT; // 7 bit address for slave plus read bit
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);// trigger 
  wait_for_completion;

  TWCR = (1 << TWINT) | (1 << TWEN);// trigger with master sending ack
  wait_for_completion;
  
  StopI2C_Trans();
}

unsigned char read_Data(){
  return TWDR;    // returning stored TWDR from Read_Acc
}
