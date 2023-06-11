#pragma once

#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>


const uint16_t  SERIAL_BAUDRATE        = 9600;
const uint8_t   SERIAL_RX_PIN          = 25;
const uint8_t   SERIAL_TX_PIN          = 33;
const uint8_t   SERIAL_AUX_PIN         = 4;
const uint8_t   SERIAL_MD0_PIN         = 13;
const uint8_t   SERIAL_MD1_PIN         = 14;


const uint8_t   MPU6050_SCL_PIN        = 26;
const uint8_t   MPU6050_SDA_PIN        = 27;


const uint8_t   QMC5883_SCL_PIN        = 0;
const uint8_t   QMC5883_SDA_PIN        = 15;


const uint8_t   BMP280_SCL_PIN         = 0;
const uint8_t   BMP280_SDA_PIN         = 15;


const uint8_t   MOTOR0_PIN             = 16;
const uint8_t   MOTOR1_PIN             = 17;
const uint8_t   MOTOR2_PIN             = 18;
const uint8_t   MOTOR3_PIN             = 19;
const uint16_t  MOTOR_MINIMUM_THROTTLE = 38436;
const uint16_t  MOTOR_MAXIMUM_THROTTLE = 50000;

#endif