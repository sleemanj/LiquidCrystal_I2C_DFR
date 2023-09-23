LiquidCrystal_I2C_DFR Library
=============================

LiquidCrystal API compatible library for interfacing
to "DFRobot", "YWRobot" and "SYDZ" type I2C 1602 backpacks 
using the PCF8574 I2C expander.

There are other backpacks using the same IC, but they 
assign different expander pins to the LCD.

Wiring
------

* SCL     ->     SCL (Uno: A5, Mega: 21, Leo*: SCL)
* SDA     ->     SDA (Uno: A4, Mega: 20, Leo*: SDA)
* VCC     ->     5v
* GND     ->     GND

*Arduino Leonardo users should read this thread:  http://forum.arduino.cc/index.php?topic=113431.0

Download, Install and Example
-----------------------------

* Download: https://sparks.gogo.co.nz/LiquidCrystal_I2C_DFR.zip
* Open the Arduino IDE (1.6.13+)
* Select the menu item Sketch > Import Library > Add Library
* Choose to install the LiquidCrystal_I2C_DFR.zip file you downloaded
* Now you can choose File > Examples > LiquidCrystal_I2C_DFR > Hello World

Programming
------------

See the examples in this package, and the reference for the
LiquidCrystal library...

http://arduino.cc/en/Reference/LiquidCrystal

I2C Address
-----------


This library has an auto-scanning ability for the I2C address, simply
create your display like this (see the examples)...

    LiquidCrystal_I2C_DFR lcd(0);

and the address will be found automatically, as long as you only have 
one I2C device on the bus in those ranges.  

The Hello World example will print the found I2C address on the display
itself so you that's a quick way to find it if you need to set it directly.

Most of the boards use either 0x27 or 0x3F  as the default I2C
address, that is none of the 3 address pins on the IC are grounded.

The 0x27/0x3F difference is between the main chip on the board being
either the PCF8574 or the PCF8574A

If you do need to set a different address to use for the
backpack, close (ground) these jumpers on the I2C backpack...

**PCF8574**

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

**PCF8574A**

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
