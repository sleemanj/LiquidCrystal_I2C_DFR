/**
 LiquidCrystal_I2C_DFR Library - Custom Characters
  
 Demonstrates how to add custom characters on an LCD
 display.
 
 For wiring instructions:
  https://github.com/sleemanj/LiquidCrystal_I2C_DFR
  
 For code instructions:
  http://www.arduino.cc/en/Tutorial/LiquidCrystal
  http://arduino.cc/en/Reference/LiquidCrystal
  
 Also useful:
  http://omerk.github.io/lcdchargen/
  
 History
 -------
  created21 Mar 2011
  by Tom Igoe
  Based on Adafruit's example at
  https://github.com/adafruit/SPI_VFD/blob/master/examples/createChar/createChar.pde
  modified 11 Sep 2014
  by James Sleeman (http://sparks.gogo.co.nz)
 
  This example code is in the public domain.
*/

// include the library code:
#include <Wire.h> 
#include <LiquidCrystal_I2C_DFR.h>

// Create a new LCD on default I2C address (0x27)
LiquidCrystal_I2C_DFR lcd(0x27);  

#define LCD_HEART  0
#define LCD_SMILE  1
#define LCD_FROWN  2
#define LCD_NOTE   3
#define LCD_CLOCK  4
#define LCD_TICK   5
#define LCD_CROSS  6
#define LCD_RETURN 7

// make some custom characters:
uint8_t lcd_chars[8][8] = {
  // 0: HEART
  {
    0b00000,
    0b01010,
    0b11111,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000
  },
  
  // 1: SMILE
  {
    0b00000,
    0b00000,
    0b01010,
    0b00000,
    0b00000,
    0b10001,
    0b01110,
    0b00000
  },
  
  // 2: FROWN
  {
    0b00000,
    0b00000,
    0b01010,
    0b00000,
    0b00000,
    0b00000,
    0b01110,
    0b10001
  },
  
  // 3: NOTE
  {0x2,0x3,0x2,0xe,0x1e,0xc,0x0},
  
  // 4: CLOCK
  {0x0,0xe,0x15,0x17,0x11,0xe,0x0},
  
  // 5: TICK
  {0x0,0x1,0x3,0x16,0x1c,0x8,0x0},
  
  // 6: CROSS
  {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0},
  
  // 7: RETURN
  {0x1,0x1,0x5,0x9,0x1f,0x8,0x4}
};

// This is just a counter
uint8_t i; 
 
void setup() {
   
  // set up the lcd's number of columns and rows: 
  // this must be done BEFORE you createChar()
  lcd.begin(16, 2);
  
  // load the 7 characters (max 7) into the display
  for(i = 0; i <= 7; i++)
  {
    lcd.createChar(i, lcd_chars[i]);
  }
   
  // make sure we are reset
  lcd.home();

  // Print a message to the lcd.
  lcd.print(" I "); 
  lcd.write(LCD_HEART);
  lcd.print(" Arduino! ");
  lcd.write(LCD_SMILE);

  // Display all the special characters on the 2nd line
  lcd.setCursor(0,1);
  for(i = 0; i <= 7; i++)
  {
    lcd.write(i);
    lcd.print(" ");
  }   
}

void loop() {

}
