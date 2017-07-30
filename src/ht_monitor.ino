/*
  dht_lcd.ino

  Reads the temperature and humidity from a DHT22 sensor then displays them on
  an HD44780 LCD display. Also sends the data by serial to something listening
  on that interface

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 * DHT22 data pin to digital pin 7
 * DHT pin 1 to +5V
 * DHT pin 4 to GROUND

 Uses the built in LCD library and the Adafruit DHT library.

 */

// include the library code:
#include <LiquidCrystal.h>
#include "DHT.h"

// initialize the LCD library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// initialize the DHT sensor
DHT dht(7, DHT22);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print the base text to the LCD
  //         ----------------
  lcd.print("Temp:          C");
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  //         ----------------
  lcd.print("Humidity:      %");

  // Setup the dht
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  lcd.setCursor(10, 0);
  lcd.print(t);

  lcd.setCursor(10, 1);
  lcd.print(h);

}
