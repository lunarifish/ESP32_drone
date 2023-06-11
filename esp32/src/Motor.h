#pragma once

#ifndef MOTOR_H
#define MOTOR_H

#include <cstdint>


class Motor {
private:
    static uint8_t motorCount;
    uint8_t  number;    
    uint16_t pwmDuty;
    uint16_t throttle;                      // Range 0~10000
    uint16_t referenceThrottle;
    bool isArmed;
public:
    Motor(uint8_t number);
    static void initAll();
    void init();
    void arm();
    void disarm();
    void setPWMDuty(uint16_t duty);
    void setThrottle(int16_t throttle);    // Range 0~10000
    void setReferenceThrottle(int16_t throttle);
    uint16_t getThrottle();
    int16_t getReferenceThrottle();
};

#endif