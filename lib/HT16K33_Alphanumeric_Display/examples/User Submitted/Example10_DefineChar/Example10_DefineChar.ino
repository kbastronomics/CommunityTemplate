/**************************************************************************************
 * HT16K33_Alphanumeric_Display
 *
 * Example: Example10 DefineChar
 *
 * This example is part of the HT16K33_Alphanumeric_Display Arduino library.
 *
 * This library is derived from the SparkFun Qwiic Alphanumeric Display
 * Arduino Library and retains attribution to SparkFun Electronics and
 * the original contributors where applicable.
 *
 * License: MIT
 * See LICENSE.md for complete license and attribution information.
 *
 * Distributed as-is; no warranty is given.
 **************************************************************************************/

#include <HT16K33_Alphanumeric_Display.h>
HT16K33 display;

void setup() {
  Serial.begin(115200);
  Serial.println("HT16K33 Alphanumeric  examples");
  Wire.begin(); //Join I2C bus

  //check if display will acknowledge
  if (display.begin() == false)
  {
    Serial.println("Device did not acknowledge! Freezing.");
    while(1);
  }
  Serial.println("Display acknowledged.");
  
  //Just for demo purposes, show original characters before change
  display.print("cafe");
  delay(500);
  display.print("size");
  

  //Update a, e, f, s and z to new characters
  //This change is not permanent, and lasts only for this program.
  
  //Define 14 segment bits: nmlkjihgfedcba
  display.defineChar('a', 0b01000001011000);                              
  display.defineChar('e', 0b10000001011000);
  display.defineChar('f', 0b01010101000000);
  //Also can use constants SEG_A - SEG_N to define characters
  display.defineChar('s', SEG_L | SEG_I | SEG_D); // 0b00100100001000  
  display.defineChar('z', SEG_N | SEG_G | SEG_D); // 0b10000001001000
}

void loop() 
{ 
  //Show the new characters
  delay(500);
  display.print("cafe");
  delay(500);
  display.print("size");
}
