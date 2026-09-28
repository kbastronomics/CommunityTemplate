/**************************************************************************************
 * HT16K33_Alphanumeric_Display
 *
 * Example: Example 03 PrintChar
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
  Serial.println("HT16K33 Alphanumeric  - Example 3: Print Character");
  Wire.begin(); //Join I2C bus

  //check if display will acknowledge
  if (display.begin() == false)
  {
    Serial.println("Device did not acknowledge! Freezing.");
    while(1);
  }
  Serial.println("Display acknowledged.");

  display.printChar('W', 0);
  display.printChar('H', 1);
  display.printChar('A', 2);
  display.printChar('T', 3);

  display.updateDisplay();
}

void loop(){
}
