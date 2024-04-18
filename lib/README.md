# Lab 5 Libraries

## Required Libraries

- [X] pwm
- [ ] i2c (Accelerometer)
- [X] spi (8x8 Matrix)
- [X] switch
- [X] timer

## Optional

- [ ] Clean-Up Code
  - [ ] pwm
  - [ ] i2c (Accelerometer)
  - [X] spi (8x8 Matrix)
  - [ ] switch
  - [ ] timer

## spi.cpp

   1. All communication with the 8 x 8 led matrix must be done over the SPI
   related pins.
   2. Read the 8x8 MAX7219 datasheet for setting up SPI mode.

## timer.cpp

   1. Implement a precise millisecond timer using timer 1 for switch
   debouncing.

## pwm.cpp

   1. Use a PWM output signal to change the frequency of the piezo buzzer
   to generate a chirping sound.

## switch.cpp

   1. Uses a switch to silence the audio chirping alarm.

## i2c.cpp

- 1. InitI2C()
  - Wake up I2C module on mega 2560
  - Set prescaler TWPS to 1
  - Set two wire interface bit rate register TWBR
  - Enable two wire interface
- 2. StartI2C_Trans(unsigned char SLA)
  - Clear TWINT, initiate start condition, initiate enable
  - Wait for completion
  - Set two wire data register to the SLA + write bit
  - Trigger action: Clear TWINT and initiate enable
  - Wait for completion
- 3. StopI2C_Trans()
  - Trigger action + stop condition
  - Write(unsigned char data)
  - Set two wire data register equal to incoming data
  - Trigger action
  - Wait for completion
- 4. Read_from(unsigned char SLA, unsigned Char MEMADDRESS)
  - Start a transmission to the SLA
  - Write to the MEMADDRESS
  - Clear TWINT, initiate start condition, initiate enable
  - Wait for completion
  - Set two wire data register to the SLA + read bit
  - Trigger action + master acknowledge bit
  - Wait for completion
  - Trigger action
  - Wait for completion
  - Trigger action + stop condition
- 5. unsigned char Read_data()
  - Return TWDR
