/*
  monitor.h

  Class to get the temperature and humidity from a DHT22 at regular intervals and update a LCD display and send the data over the serial interface.
 */

#ifndef monitor_h
#define monitor_h

#include <LiquidCrystal.h>
#include "DHT.h"
#include <Arduino.h>

class monitor {

private:
    unsigned long previousSerial;
    unsigned long previousScreen;
    unsigned long lastDataMillis;
    float temperature;
    float humidity;
    unsigned long screen_period; // How often to update the screen, in ms
    unsigned long serial_period; // How often to send over serial, in ms
    bool error; // Record if there was an error last time we read the sensor.

public:
    monitor(unsigned long screen_T, unsigned long serial_T);

    // Need functions to:
    // + Check time since last update
    // + Print info to screen
    // + Print info to serial

    // Pass the objects as non-const as the member functions are not const.
    // Have separate functions for the lcd and serial as the times are different
    // and the sensor needs different behaviour if it fails to read.
    void update_lcd(LiquidCrystal& lcd, DHT& dht, unsigned long currentMillis);

    void update_serial(HardwareSerial& serial, DHT& dht, unsigned long currentMillis);

    void update(LiquidCrystal& lcd, HardwareSerial& serial, DHT& dht);

    // Write the information to the serial port
    void serial_report(HardwareSerial& serial);

    // Print the information on the screen
    void show_on_screen(LiquidCrystal& lcd) const;
};

#endif
