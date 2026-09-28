/**************************************************************************************
 * HT16K33_Alphanumeric_Display
 *
 * Example: turn on all segs
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

#include <HT16K33_Alphanumeric_Display.h> //Click here to get the library: http://librarymanager/All#Alphanumeric_Display by SparkFun
HT16K33 display;

void setup()
{
  Serial.begin(115200);
  Serial.println("HT16K33 Alphanumeric  examples");

  Wire.begin(); //Join I2C bus

  if (display.begin(0x71) == false)
  {
    Serial.println("Device did not acknowledge! Freezing.");
    while (1);
  }
  Serial.println("Display acknowledged.");

  display.setBrightness(15);
  display.print("\t\t\t\t");  //Unknown char turns on all segements!
  display.decimalOn();
  display.colonOn();
}

void loop()
{
//  for (uint8_t i = 0; i < 17; i++){
//    display.setBrightness(i);
//    display.print("\t\t\t\t");  //Unknown char turns on all segements!
//    display.decimalOn();
//    display.colonOn();
//    delay(1000);
//  }
}
