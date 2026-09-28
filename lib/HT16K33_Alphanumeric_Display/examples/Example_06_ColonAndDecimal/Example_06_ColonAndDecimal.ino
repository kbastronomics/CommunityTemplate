/**************************************************************************************
 * HT16K33_Alphanumeric_Display
 *
 * Example: Example 06 ColonAndDecimal
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

void setup(){
  Serial.begin(115200);
  Serial.println("HT16K33 Alphanumeric  - Example 6: Colon And Decimal");

  Wire.begin();

  if (display.begin() == false)
  {
    Serial.println("Device did not acknowledge! Freezing.");
    while(1);
  }
  Serial.println("Display acknowledged.");

  //You can print colons and decimals
  //NOTE: they can only go in the character position determined by the layout of the display
  display.print("12:3.4");
  
//  display.decimalOn();  //Turn decimals on
//  display.decimalOff();   //Turn decimals off
//  display.decimalOnSingle(0); //Turn decimal on for one display
//  display.colonOn();      //Turn colons on
//  display.colonOff();     //Turn colons off
//  display.colonOnSingle(1); //Turn colon on for one display
}

void loop()
{
}
