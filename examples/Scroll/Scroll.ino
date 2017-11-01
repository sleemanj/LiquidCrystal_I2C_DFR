/**
 LiquidCrystal_I2C_DFR Library - scrollDisplayLeft() and scrollDisplayRight()
  
 This sketch prints "Hello World!" to the LCD and uses the
 scrollDisplayLeft() and scrollDisplayRight() methods to scroll
 the text.
 
 For wiring instructions:
  https://github.com/sleemanj/LiquidCrystal_I2C_DFR
  
 For code instructions:
  http://arduino.cc/en/Tutorial/LiquidCrystalScroll
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
  delay(1000);
}

void loop() {
  // scroll 13 positions (string length) to the left 
  // to move it offscreen left:
  for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft(); 
    // wait a bit:
    delay(150);
  }

  // scroll 29 positions (string length + display length) to the right
  // to move it offscreen right:
  for (int positionCounter = 0; positionCounter < 29; positionCounter++) {
    // scroll one position right:
    lcd.scrollDisplayRight(); 
    // wait a bit:
    delay(150);
  }
  
    // scroll 16 positions (display length + string length) to the left
    // to move it back to center:
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft(); 
    // wait a bit:
    delay(150);
  }
  
  // delay at the end of the full loop:
  delay(1000);

}

