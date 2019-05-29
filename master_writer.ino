// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
}

byte x = 56;

void loop()
{
 
  Wire.beginTransmission(x);
  
  
  Wire.write(1);  

  delay(500);

  Wire.write(0); 


  Wire.endTransmission();    // stop transmitting
  delay(500);
  
}
