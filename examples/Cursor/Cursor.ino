/**
 LiquidCrystal_I2C_DFR Library - Cursor
  
 This sketch prints "Hello World!" to the LCD and
 uses the cursor()  and noCursor() methods to turn
 on and off the cursor.
 
 For wiring instructions:
  https://github.com/sleemanj/LiquidCrystal_I2C_DFR
  
 For code instructions:
  http://arduino.cc/en/Tutorial/LiquidCrystalCursor
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

// Create a new LCD on auto-scanned I2C Address
// If you need to specify the address directly, you can use
//   LiquidCrystal_I2C_DFR lcd(0x27);
// where the address is 0x27 for example
LiquidCrystal_I2C_DFR lcd(0);  

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  // Turn off the cursor:
  lcd.noCursor();
  delay(500);
   // Turn on the cursor:
  lcd.cursor();
  delay(500);
}

