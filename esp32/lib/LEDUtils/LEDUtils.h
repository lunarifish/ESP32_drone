#ifndef LEDUTILS_H
#define LEDUTILS_H

#include <cstdint>


class LED {
public:
    LED(uint8_t pin);
    void blink(uint8_t times, uint16_t time_interval);
private:
    uint8_t pin;
};


#endif