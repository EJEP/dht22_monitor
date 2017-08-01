/*
  monitor.cpp

  Class to get the temperature and humidity from a DHT22 at regular intervals and update a LCD display and send the data over the serial interface.
*/
#include <LiquidCrystal.h>
#include "DHT.h"

#include "monitor.h"

monitor::monitor(long screen_T, long serial_T) {
    screen_period = screen_T;
    serial_period = serial_T;
    previousMillis = 0;
    error = false;
}

// Pass the objects as non-const as the member functions are not const.
void monitor::update(LiquidCrystal& lcd, DHT& dht, HardwareSerial& serial) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= screen_period) {
        // Need to get new data
        temperature = dht.readTemperature();
        humidity = dht.readHumidity();
        // Try and do some error handling. There may be a better way.
        if (isnan(temperature) || isnan(humidity)) {
            //     return;
            lcd.clear();
            lcd.print("E R R O R");
            error = true;
        }
        else {
            if (error == true) {
                lcd.begin(16, 2);
                lcd.print("Temp:          C");
                lcd.setCursor(0, 1);
                lcd.print("Humidity:      %");
            }
            // Actually update the LCD
            show_on_screen(lcd);

            // Test serial output
            serial.print("Temp = ");
            serial.println(temperature);
            error = false;
        }

        previousMillis += screen_period;
    }
}

void monitor::show_on_screen(LiquidCrystal& lcd) const {
    // Position the cursor in the spaces and print the data
    lcd.setCursor(10, 0);
    lcd.print(temperature);
    lcd.setCursor(10, 1);
    lcd.print(humidity);
}
