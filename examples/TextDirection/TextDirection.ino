/**
 LiquidCrystal_I2C_DFR Library - TextDirection
  
 This sketch demonstrates how to use leftToRight() and rightToLeft()
 to move the cursor.
 
 For wiring instructions:
  https://github.com/sleemanj/LiquidCrystal_I2C_DFR
  
 For code instructions:
  http://arduino.cc/en/Tutorial/LiquidCrystalTextDirection
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

int thisChar = 'a';

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // turn on the cursor:
  lcd.cursor();
}

void loop() {
  // reverse directions at 'm':
  if (thisChar == 'm') {
    // go right for the next letter
    lcd.rightToLeft(); 
  }
  // reverse again at 's':
  if (thisChar == 's') {
    // go left for the next letter
    lcd.leftToRight(); 
  }
  // reset at 'z':
  if (thisChar > 'z') {
    // go to (0,0):
    lcd.home(); 
    // start again at 0
    thisChar = 'a';
  }
  // print the character
  lcd.write(thisChar);
  // wait a second:
  delay(1000);
  // increment the letter:
  thisChar++;
}








