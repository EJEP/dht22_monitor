# DHt22 Monitor #

Arduino code to read the temperature and humidity from a DHT22 sensor. They are displayed on an LCD screen and sent over serial.

## Requirements ##

### Code ###

The directories are set up for [PlatformIO](https://platformio.org/) rather than the default arduino IDE. The code will work fine with the default IDE though.

+ The Adafruit UnifiedSensor [library](https://github.com/adafruit/Adafruit_Sensor)
+ The Adafruit [DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library)
+ LiquidCrystal library

Note that there is an error with the init sequence in the Adafruit [DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library). This is discussed in a [bug report](https://github.com/adafruit/DHT-sensor-library/issues/48).

### Hardware ###

+ DHT22 sensor
+ HD44780 LCD display

## Usage ##

The temperature and humidity are displayed on the LCD screen, and sent over serial. The intervals for updating the reports are set in the constructor for the `monitor` class.
