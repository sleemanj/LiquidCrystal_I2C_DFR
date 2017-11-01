/*
 
 LiquidCrystal_I2C_DFR Library
 =============================
  
 LiquidCrystal API compatible library for interfacing
 to "DFRobot", "YWRobot" and "SYDZ" type I2C 1602 backpacks 
 using the PCF8574 I2C expander.
 
 There are other backpacks using the same IC, but they 
 assign different expander pins to the LCD.
 
 Wiring
 ------
 
 * SCL     ->     SCL (A5, Use Pin 21 on the Arduino Mega)
 * SDA     ->     SDA (A4, Use Pin 20 on the Arduino Mega)
 * VCC     ->     5v
 * GND     ->     GND
 
 Programming
 ------------
 
 See the examples in this package, and the reference for the
 LiquidCrystal library...
 
 http://arduino.cc/en/Reference/LiquidCrystal
  
 I2C Address
 -----------
 
 This library has an auto-scanning ability for the I2C address, simply
 do
   
   LiquidCrystal_I2C_DFR lcd(0);
 
 and the address will be found automatically, as long as you only have 
 one I2C device on the bus in those ranges.
 
 Most of the boards use either 0x27 or 0x3F  as the default I2C
 address, that is none of the 3 address pins on the IC are grounded.
 
 The 0x27/0x3F difference is between the PCF8574 and the PCF8574A 
 variants which have different address spaces.
 
 If you do need to set a different address to use for the
 backpack, close (ground) these jumpers on the I2C backpack...
 
  PCF8574 
 
 | Adr      | A0  |  A1  | A2  |
 | -------- | --- |  --- | --- |
 | 0x27     |     |      |     |
 | 0x26     |     |      |  X  |
 | 0x25     |     |   X  |     |
 | 0x24     |     |   X  |  X  |
 | 0x23     | X   |      |     |
 | 0x22     | X   |      |  X  |
 | 0x21     | X   |   X  |     |
 | 0x20     | X   |   X  |  X  |
 
 PCF8574A
 
 | Adr      | A0  |  A1  | A2  |
 | -------- | --- |  --- | --- |
 | 0x3F     |     |      |     |
 | 0x3E     |     |      |  X  |
 | 0x3D     |     |   X  |     |
 | 0x3C     |     |   X  |  X  |
 | 0x3B     | X   |      |     |
 | 0x3A     | X   |      |  X  |
 | 0x39     | X   |   X  |     |
 | 0x38     | X   |   X  |  X  |
 

History/Lineage/See Also
------------------------

The lineage of this code can be traced to:
   The original LiquidCrystal library, to which this library
   is compatible.
     http://arduino.cc/en/Reference/LiquidCrystal
   
   From which an I2C implementation was created:
     http://hmario.home.xs4all.nl/arduino/LiquidCrystal_I2C/
 
   Which was modified by DFRobot for it's boards:
     http://www.dfrobot.com/wiki/index.php?title=I2C/TWI_LCD1602_Module_(SKU:_DFR0063)
     
   And was modified slightly by other China based manufacturers
   for their boards (notably "YWRobot" and "SYDZ", and some unnamed ones).
             
*/

#include "LiquidCrystal_I2C_DFR.h"
#include <inttypes.h>
#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#define printIIC(args)	Wire.write(args)
inline size_t LiquidCrystal_I2C_DFR::write(uint8_t value) {
	send(value, Rs);
	return 1;
}

#else
#include "WProgram.h"

#define printIIC(args)	Wire.send(args)
inline void LiquidCrystal_I2C_DFR::write(uint8_t value) {
	send(value, Rs);
}

#endif
#include "Wire.h"


// When the display powers up, it is configured as follows:
//
// 1. Display clear
// 2. Function set: 
//    DL = 1; 8-bit interface data 
//    N = 0; 1-line display 
//    F = 0; 5x8 dot character font 
// 3. Display on/off control: 
//    D = 0; Display off 
//    C = 0; Cursor off 
//    B = 0; Blinking off 
// 4. Entry mode set: 
//    I/D = 1; Increment by 1
//    S = 0; No shift 
//
// Note, however, that resetting the Arduino doesn't reset the LCD, so we
// can't assume that its in that state when a sketch starts (and the
// LiquidCrystal constructor is called).

LiquidCrystal_I2C_DFR::LiquidCrystal_I2C_DFR(uint8_t lcd_Addr)
{
  _Addr = lcd_Addr;
  _backlightval = LCD_BACKLIGHT;
}

void LiquidCrystal_I2C_DFR::begin(uint8_t cols, uint8_t lines, uint8_t dotsize) {
  Wire.begin();
  
  // We have to do this after Wire.begin
  uint8_t scanAddress = 0x20;
  while(_Addr == 0 )
  {
    Wire.beginTransmission(scanAddress);
    if(Wire.endTransmission() == 0)
    {
      _Addr = scanAddress;
      break;
    }
    
    if(scanAddress == 0x27) 
    {
      // Have scanned all of the first range, try the next range
      scanAddress = 0x38;
    }
    else if(scanAddress == 0x3F) 
    {
      // Have scanned both ranges, not found
      break;
    }
    else
    {
      // Try next address in the range
      scanAddress++;
    }
  }
    
  _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
  _cols = cols;
  _rows = lines;
  
	if (lines > 1) {
		_displayfunction |= LCD_2LINE;
	}
	_numlines = lines;

	// for some 1 line displays you can select a 10 pixel high font
	if ((dotsize != 0) && (lines == 1)) {
		_displayfunction |= LCD_5x10DOTS;
	}

	// SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
	// according to datasheet, we need at least 40ms after power rises above 2.7V
	// before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
	delay(50); 
  
	// Now we pull both RS and R/W low to begin commands
	expanderWrite(_backlightval);	// reset expanderand turn backlight off (Bit 8 =1)
	delay(1000);

  	//put the LCD into 4 bit mode
	// this is according to the hitachi HD44780 datasheet
	// figure 24, pg 46
	
	  // we start in 8bit mode, try to set 4 bit mode
   write4bits(0x03 << 4);
   delayMicroseconds(4500); // wait min 4.1ms
   
   // second try
   write4bits(0x03 << 4);
   delayMicroseconds(4500); // wait min 4.1ms
   
   // third go!
   write4bits(0x03 << 4); 
   delayMicroseconds(150);
   
   // finally, set to 4-bit interface
   write4bits(0x02 << 4); 


	// set # lines, font size, etc.
	command(LCD_FUNCTIONSET | _displayfunction);  
	
	// turn the display on with no cursor or blinking default
	_displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	display();
	
	// clear it off
	clear();
	
	// Initialize to default text direction (for roman languages)
	_displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	
	// set the entry mode
	command(LCD_ENTRYMODESET | _displaymode);
	
	home();
  
}

/********** high level commands, for the user! */
void LiquidCrystal_I2C_DFR::clear(){
	command(LCD_CLEARDISPLAY);// clear display, set cursor position to zero
	delayMicroseconds(2000);  // this command takes a long time!
}

void LiquidCrystal_I2C_DFR::home(){
	command(LCD_RETURNHOME);  // set cursor position to zero
	delayMicroseconds(2000);  // this command takes a long time!
}

void LiquidCrystal_I2C_DFR::setCursor(uint8_t col, uint8_t row){
	int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
	if ( row > _numlines ) {
		row = _numlines-1;    // we count rows starting w/0
	}
	command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

// Turn the display on/off (quickly)
void LiquidCrystal_I2C_DFR::noDisplay() {
	_displaycontrol &= ~LCD_DISPLAYON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LiquidCrystal_I2C_DFR::display() {
	_displaycontrol |= LCD_DISPLAYON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off
void LiquidCrystal_I2C_DFR::noCursor() {
	_displaycontrol &= ~LCD_CURSORON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LiquidCrystal_I2C_DFR::cursor() {
	_displaycontrol |= LCD_CURSORON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor
void LiquidCrystal_I2C_DFR::noBlink() {
	_displaycontrol &= ~LCD_BLINKON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LiquidCrystal_I2C_DFR::blink() {
	_displaycontrol |= LCD_BLINKON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM
void LiquidCrystal_I2C_DFR::scrollDisplayLeft(void) {
	command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void LiquidCrystal_I2C_DFR::scrollDisplayRight(void) {
	command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void LiquidCrystal_I2C_DFR::leftToRight(void) {
	_displaymode |= LCD_ENTRYLEFT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void LiquidCrystal_I2C_DFR::rightToLeft(void) {
	_displaymode &= ~LCD_ENTRYLEFT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor
void LiquidCrystal_I2C_DFR::autoscroll(void) {
	_displaymode |= LCD_ENTRYSHIFTINCREMENT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor
void LiquidCrystal_I2C_DFR::noAutoscroll(void) {
	_displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void LiquidCrystal_I2C_DFR::createChar(uint8_t location, uint8_t charmap[]) {
	location &= 0x7; // we only have 8 locations 0-7
	command(LCD_SETCGRAMADDR | (location << 3));
	for (int i=0; i<8; i++) {
		write(charmap[i]);
	}
}

// Turn the (optional) backlight off/on
void LiquidCrystal_I2C_DFR::noBacklight(void) {
	_backlightval=LCD_NOBACKLIGHT;
	expanderWrite(0);
}

void LiquidCrystal_I2C_DFR::backlight(void) {
	_backlightval=LCD_BACKLIGHT;
	expanderWrite(0);
}



/*********** mid level commands, for sending data/cmds */

inline void LiquidCrystal_I2C_DFR::command(uint8_t value) {
	send(value, 0);
}


/************ low level data pushing commands **********/

// write either command or data
void LiquidCrystal_I2C_DFR::send(uint8_t value, uint8_t mode) {
	uint8_t highnib=value&0xf0;
	uint8_t lownib=(value<<4)&0xf0;
       write4bits((highnib)|mode);
	write4bits((lownib)|mode); 
}

void LiquidCrystal_I2C_DFR::write4bits(uint8_t value) {
	expanderWrite(value);
	pulseEnable(value);
}

void LiquidCrystal_I2C_DFR::expanderWrite(uint8_t _data){                                        
	Wire.beginTransmission(_Addr);
	printIIC((int)(_data) | _backlightval);
	Wire.endTransmission();   
}

void LiquidCrystal_I2C_DFR::pulseEnable(uint8_t _data){
	expanderWrite(_data | En);	// En high
	delayMicroseconds(1);		// enable pulse must be >450ns
	
	expanderWrite(_data & ~En);	// En low
	delayMicroseconds(50);		// commands need > 37us to settle
} 


// Alias functions

void LiquidCrystal_I2C_DFR::cursor_on(){
	cursor();
}

void LiquidCrystal_I2C_DFR::cursor_off(){
	noCursor();
}

void LiquidCrystal_I2C_DFR::blink_on(){
	blink();
}

void LiquidCrystal_I2C_DFR::blink_off(){
	noBlink();
}

void LiquidCrystal_I2C_DFR::load_custom_character(uint8_t char_num, uint8_t *rows){
		createChar(char_num, rows);
}

void LiquidCrystal_I2C_DFR::setBacklight(uint8_t new_val){
	if(new_val){
		backlight();		// turn backlight on
	}else{
		noBacklight();		// turn backlight off
	}
}

void LiquidCrystal_I2C_DFR::printstr(const char c[]){
	//This function is not identical to the function used for "real" I2C displays
	//it's here so the user sketch doesn't have to be changed 
	print(c);
}


// unsupported API functions
void LiquidCrystal_I2C_DFR::off(){}
void LiquidCrystal_I2C_DFR::on(){}
void LiquidCrystal_I2C_DFR::setDelay (int cmdDelay,int charDelay) {}
uint8_t LiquidCrystal_I2C_DFR::status(){return 0;}
uint8_t LiquidCrystal_I2C_DFR::keypad (){return 0;}
uint8_t LiquidCrystal_I2C_DFR::init_bargraph(uint8_t graphtype){return 0;}
void LiquidCrystal_I2C_DFR::draw_horizontal_graph(uint8_t row, uint8_t column, uint8_t len,  uint8_t pixel_col_end){}
void LiquidCrystal_I2C_DFR::draw_vertical_graph(uint8_t row, uint8_t column, uint8_t len,  uint8_t pixel_row_end){}
void LiquidCrystal_I2C_DFR::setContrast(uint8_t new_val){}

	
