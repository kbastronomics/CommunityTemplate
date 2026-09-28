/**************************************************************************************
 * HT16K33_Alphanumeric_Display
 *
 * Example: Example 08 MultiDisplay
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

#include <HT16K33_Alphanumeric_Display.h>  //Click here to get the library: http://librarymanager/All#SparkFun_Qwiic_Alphanumeric_Display by SparkFun
HT16K33 display;

void setup() {
  Serial.begin(115200);
  Serial.println("HT16K33 Alphanumeric  - Example 8: Multi Display");
  Wire.begin(); //Join I2C bus

  //check if displays will acknowledge
  //The first address in the begin() function should be the left-most display, traveling to the right from there
  //This is how the string will print across displays, reading from left to right.
  if (display.begin(0x70, 0x71) == false)
  {
    Serial.println("Device did not acknowledge! Freezing.");
    while(1);
  }
  Serial.println("Displays acknowledged.");

  display.print("Get Milk");
}

void loop() 
{
}
