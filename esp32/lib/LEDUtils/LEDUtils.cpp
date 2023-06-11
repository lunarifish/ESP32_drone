#include "LEDUtils.h"
#include <Arduino.h>


LED::LED(uint8_t pin): pin(pin) {
    pinMode(pin, OUTPUT);
}

void LED::blink(uint8_t times, uint16_t time_interval) {
    for (int i = 0; i < times; i++) {
        digitalWrite(pin, HIGH);
        delay(time_interval);
        digitalWrite(pin, LOW);
        delay(time_interval);
    }
}