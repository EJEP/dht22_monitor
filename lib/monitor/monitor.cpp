/*
  monitor.cpp

  Class to get the temperature and humidity from a DHT22 at regular intervals
  and update a LCD display and send the data over the serial interface.
*/
#include <LiquidCrystal.h>
#include "DHT.h"

#include "monitor.h"

monitor::monitor(long screen_T, long serial_T) {
    screen_period = screen_T;
    serial_period = serial_T;
    previousMillis = 0;
    lastDataMillis = 0;
    error = false;
}

// Pass the objects as non-const as the member functions are not const.
void monitor::update_lcd(LiquidCrystal& lcd, DHT& dht, unsigned long currentMillis) {
    if (currentMillis - previousScreen >= screen_period) {
        // Get new data if last data was more than 5 seconds ago
        if (currentMillis - lastDataMillis >= 5000) {
            // Need to get new data
            temperature = dht.readTemperature();
            humidity = dht.readHumidity();
            lastDataMillis += 5000;
        }

        // Try and do some error handling. There may be a better way.
        if (isnan(temperature) || isnan(humidity)) {
            //     return;
            lcd.clear();
            lcd.print("E R R O R");
            error = true;
        }
        else {
            if (error == true) {
                lcd.clear;
                lcd.setCursor(0, 0);
                lcd.print("Temp:          C");
                lcd.setCursor(0, 1);
                lcd.print("Humidity:      %");
            }
            // Actually update the LCD
            show_on_screen(lcd);

            error = false;
        }

        previousScreen += screen_period;
    }
}

void monitor::update_serial(HardwareSerial& serial, DHT& dht, unsigned long currentMillis) {
    if (currentMillis - previousSerial >= screen_period) {
        // Get new data if last data was more than 5 seconds ago
        if (currentMillis - lastDataMillis >= 5000) {
            // Need to get new data
            temperature = dht.readTemperature();
            humidity = dht.readHumidity();
            lastDataMillis += 5000;
        }

        if (isnan(temperature) || isnan(humidity)) {
            error = true;
        }

        else {
            serial_report(serial);
            error = false;
        }
        previousSerial += serial_period;
    }
}

void monitor::update(LiquidCrystal& lcd, HardwareSerial& serial, DHT& dht) {
    // Get the time since the last update
    unsigned long currentMillis = millis();

    // Update the LCD if more time than the screen period has passed
    if (currentMillis - previousScreen >= screen_period) {
        // Get new data if last data was more than 5 seconds ago
        if (currentMillis - lastDataMillis >= 5000) {
            // Need to get new data
            temperature = dht.readTemperature();
            humidity = dht.readHumidity();
            lastDataMillis += 5000;
        }

        // Try and do some error handling. There may be a better way.
        if (isnan(temperature) || isnan(humidity)) {
            //     return;
            lcd.clear();
            lcd.print("E R R O R");
            error = true;
        }
        else {
            // Actually update the LCD
            show_on_screen(lcd);

            error = false;
        }
        previousScreen += screen_period;
    }

    if (currentMillis - previousSerial >= screen_period) {
        // Get new data if last data was more than 5 seconds ago
        if (currentMillis - lastDataMillis >= 5000) {
            // Need to get new data
            temperature = dht.readTemperature();
            humidity = dht.readHumidity();
            lastDataMillis += 5000;
        }

        if (isnan(temperature) || isnan(humidity)) {
            error = true;
        }

        else {
            serial_report(serial);
            error = false;
        }
        previousSerial += serial_period;
    }

}

void monitor::serial_report(HardwareSerial& serial) {
    serial.println(temperature)
}

void monitor::show_on_screen(LiquidCrystal& lcd) const {
    // Position the cursor in the spaces and print the data
    lcd.setCursor(10, 0);
    lcd.print(temperature);
    lcd.setCursor(10, 1);
    lcd.print(humidity);
}
