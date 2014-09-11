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

Download, Install and Example
-----------------------------

* Download: http://sparks.gogo.co.nz/LiquidCrystal_I2C_DFR.zip
* Open the Arduino IDE (1.0.5)
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
There are three jumper/pads on these types of boards marked A0, 
A1 and A2.  These jumpers are pulled high, if you solder across 
the two pads of a jumper it will "close" the jumper.

With these jumpers open the address is 0x27, this is the default
setting.

If you do need to set a different address to use for the
backpack, close (ground) these jumpers on the I2C backpack...

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
