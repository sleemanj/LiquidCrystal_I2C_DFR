/**
 LiquidCrystal_I2C_DFR Library - Blink
  
 This sketch prints "Hello World!" to the LCD and makes the 
 cursor block blink.
 
 For wiring instructions:
  https://github.com/sleemanj/LiquidCrystal_I2C_DFR
  
 For code instructions:
  http://arduino.cc/en/Tutorial/LiquidCrystalBlink
  http://arduino.cc/en/Reference/LiquidCrystal
  
 History
 -------
  Library originally added 18 Apr 2008
  by David A. Mellis
  library modified 5 Jul 2009
  by Limor Fried (http://www.ladyada.net)
  example added 9 Jul 2009
  by Tom Igoe 
  modified 22 Nov 2010
  by Tom Igoe
  modified 11 Sep 2014
  by James Sleeman (http://sparks.gogo.co.nz)
 
  This example code is in the public domain.
*/


// include the library code:
#include <Wire.h> 
#include <LiquidCrystal_I2C_DFR.h>

// Create a new LCD on default I2C address (0x27)
LiquidCrystal_I2C_DFR lcd(0x27);  

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  // Turn off the blinking cursor:
  lcd.noBlink();
  delay(3000);
   // Turn on the blinking cursor:
  lcd.blink();
  delay(3000);
}


