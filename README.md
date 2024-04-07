# ECE372-Lab5

You will use the MPU 6050 accelerometer module and I2C serial
communication protocol to read and print the measured X, Y, and Z data
accelerometer from the module. You will also detect changes in either Y
and Z axis rotation above a predetermined threshold level (~ 45 degrees
for each axis). This threshold level will determine the state of the
8x8 LED matrix display and whether a buzzer alarm sounds off.

You will interface with the 8 x 8 LED matrix using the SPI
communication protocol. While the MPU 6050 accelerometer is below the
threshold level that you determine, you will display a smiley face on
the 8 x 8 LED matrix. When the MPU 6050 accelerometer goes above the
threshold level, the smiley face turns to a frowny face on the 8 x 8
led matrix display.

You will also implement a buzzer alarm that produces a chirping sound
when the accelerometer sensor goes above a certain threshold value.
A push button switch will silence the piezo alarm
