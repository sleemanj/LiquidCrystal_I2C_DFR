/**
 LiquidCrystal_I2C_DFR Library - Hello World
  
 This sketch prints "Hello World!" to the LCD
 and shows the time.
 
 For wiring instructions:
  https://github.com/sleemanj/LiquidCrystal_I2C_DFR
  
 For code instructions:
  http://www.arduino.cc/en/Tutorial/LiquidCrystal
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

void setup()
{
  // Start the 16x2 LCD
  lcd.begin(16,2);
 
  // Turn on the backlight
  lcd.backlight();
  
  // And give a nice message.
  lcd.print("Hello World!");
  lcd.setCursor(0, 1);
  lcd.print("    I2C Addr: ");
  lcd.print(lcd.getAddress(), HEX);
  delay(2500);
}

void loop()
{
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis()/1000);
}
