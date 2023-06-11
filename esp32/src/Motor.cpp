#include "Motor.h"
#include "Config.h"
#include <Arduino.h>

uint8_t Motor::motorCount = 0;

Motor::Motor(uint8_t number): 
    number(number), 
    isArmed(false), 
    throttle(0), 
    referenceThrottle(0) 
    {
    ledcSetup(number, 50, 16);
    setPWMDuty(MOTOR_MINIMUM_THROTTLE);

    switch (number) {
        case 0: ledcAttachPin(MOTOR0_PIN, 0); break;
        case 1: ledcAttachPin(MOTOR1_PIN, 1); break;
        case 2: ledcAttachPin(MOTOR2_PIN, 2); break;
        case 3: ledcAttachPin(MOTOR3_PIN, 3); break;
        default: throw number;
    }

    motorCount++;
}

void Motor::init() {
    setPWMDuty(MOTOR_MAXIMUM_THROTTLE);
    delay(2200);
    setPWMDuty(MOTOR_MINIMUM_THROTTLE);
    delay(8800);
}

void Motor::initAll() {
    for (uint8_t i = 0; i < motorCount; i++) ledcWrite(i, MOTOR_MAXIMUM_THROTTLE);
    delay(2200);
    for (uint8_t i = 0; i < motorCount; i++) ledcWrite(i, MOTOR_MINIMUM_THROTTLE);
    delay(8800);
}

void Motor::arm() {
    setPWMDuty(MOTOR_MINIMUM_THROTTLE);
    throttle = 0;
    referenceThrottle = 0;
    isArmed = true;
}

void Motor::disarm() {
    setPWMDuty(0);
    throttle = 0;
    referenceThrottle = 0;
    isArmed = false;
}

void Motor::setPWMDuty(uint16_t duty) {
    ledcWrite(number, duty);
    pwmDuty = duty;
}

void Motor::setThrottle(int16_t throttle) {
    if (isArmed) {
        if (throttle <= 10000 && throttle >= 0) {
            this->throttle = throttle;
            throttle = ((uint16_t)((MOTOR_MAXIMUM_THROTTLE - MOTOR_MINIMUM_THROTTLE) * (static_cast<double>(throttle) / 10000)) + MOTOR_MINIMUM_THROTTLE);
            setPWMDuty(throttle);
        } else if (throttle < 0) {
            this->throttle = 0;
            setPWMDuty(MOTOR_MINIMUM_THROTTLE);
        } else {
            this->throttle = 10000;
            setPWMDuty(MOTOR_MAXIMUM_THROTTLE);
        }
    } else {
        Serial.print("Motor");
        Serial.print(number);
        Serial.println(" is not armed");
    }
}

void Motor::setReferenceThrottle(int16_t throttle) {
    if (isArmed) {
        if (throttle <= 10000 && throttle >= 0) {
            referenceThrottle = throttle;
        } else if (throttle < 0) {
            referenceThrottle = 0;
        } else {
            referenceThrottle = 10000;
        }
    } else {
        Serial.print("Motor");
        Serial.print(number);
        Serial.println(" is not armed");
    }
}

uint16_t Motor::getThrottle() {
    return throttle;
}

int16_t Motor::getReferenceThrottle() {
    return (int32_t)referenceThrottle;
}