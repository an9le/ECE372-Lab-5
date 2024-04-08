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

# Instructions:
You will need to create a circuit using your breadboard, jumper wires,
accelerometer, 8x8 led matrix, piezo speaker and a push button switch.
There should be no special function registers used in the code for
main(). Arduino libraries for Serial.println can be used for printing
x,y, and z accelerometer data and also debugging. You will need to
build your own timer function for delays when needed.

Read the MPU 6050 accelerometer datasheets. You will use the WHO_AM_I
register (pg. 46 of register map) as the SLA. The register that you
will be reading from are the ACCEL_nOUT registers (pg. 30 of register
map). There are two 8-bit registers for X, Y, and Z. These registers
will need to be read and combined to gather the necessary information.
Finally, you need to obtain the power management register information
(pg. 41 of register map). Before developing your threshold values, you
should verify that data changes in all orthogonal x,y and z directions.

You will need to determine your accelerometer threshold tilt value
(approximately 45degrees from rest position) based on actual readings
that you obtain.

Read the 8x8 LED Matrix display datasheet (MAX7221 on how to interface
the LED matrix using SPI protocol.

Use the passive piezo buzzer device. The alarm sound should be a
chirping sound.

