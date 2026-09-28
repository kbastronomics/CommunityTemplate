/**************************************************************************************
 * HT16K33_Alphanumeric_Display
 *
 * Example: Example 02 TurnOnOneSegment
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

void setup()
{
  Serial.begin(115200);
  Serial.println("HT16K33 Alphanumeric  - Example 2: Turn On One Segment");
  Wire.begin(); //Join I2C bus

  //check if display will acknowledge
  if (display.begin() == false)
  {
    Serial.println("Device did not acknowledge! Freezing.");
    while(1);
  }
  Serial.println("Display acknowledged.");

  display.illuminateSegment('A', 0);
  display.illuminateSegment('L', 1);
  display.illuminateSegment('I', 2);
  display.illuminateSegment('G', 3);
  display.updateDisplay();
}

void loop()
{
}
