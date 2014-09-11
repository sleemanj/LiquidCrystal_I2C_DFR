/**
 LiquidCrystal_I2C_DFR Library - Serial Input
  
 This sketch displays text sent over the serial port 
 (e.g. from the Serial Monitor) on an attached LCD.
 
 For wiring instructions:
  https://github.com/sleemanj/LiquidCrystal_I2C_DFR
  
 For code instructions:
  http://arduino.cc/en/Tutorial/LiquidCrystalSerial
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

#include <Wire.h> 
#include <LiquidCrystal_I2C_DFR.h>

// Create a new LCD on default I2C address (0x27)
LiquidCrystal_I2C_DFR lcd(0x27);  

void setup()
{  
  // Start the 16x2 LCD
  lcd.begin(16,2);
  
  // Turn on the backlight
  lcd.backlight();
  lcd.print(" Send Text From");
  lcd.setCursor(0,1);
  lcd.print(" Serial Monitor");
  
  Serial.begin(9600);
}

void loop()
{
  // when characters arrive over the serial port...
  if (Serial.available()) {
    // wait a bit for the entire message to arrive
    delay(100);
    // clear the screen
    lcd.clear();
    // read all the available characters
    while (Serial.available() > 0) {
      // display each character to the LCD
      lcd.write(Serial.read());
    }
  }
}