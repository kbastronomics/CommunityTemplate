/**************************************************************************************
 * HT16K33_Alphanumeric_Display
 *
 * Example: 4 displays
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

#include <Wire.h>

#include <HT16K33_Alphanumeric_Display.h>  //Click here to get the library: http://librarymanager/All#Alphanumeric_Display by SparkFun
HT16K33 display;

void setup() {
  Serial.begin(115200);
  Serial.println("HT16K33 Alphanumeric  examples");
  Wire.begin(); //Join I2C bus

  //check if displays will acknowledge
//  if (display.begin(0x70) == false)
//  if (display.begin(0x70, 0x71) == false)
//  if (display.begin(0x70, 0x71, 0x72) == false)
  if (display.begin(0x70, 0x71, 0x72, 0x73) == false)
  {
    Serial.println("Device did not acknowledge! Freezing.");
    while(1);
  }
  Serial.println("Displays acknowledged.");

  display.setBrightness(1);
//  display.setBlinkRate(2);

//  display.print("hell");
//  display.print("hello st");
//  display.print("hello stinky");
  display.print("hello stinky poo");
}

void loop() 
{
}
