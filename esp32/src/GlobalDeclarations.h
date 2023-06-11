#ifndef GLOBAL_DECLARATIONS_H
#define GLOBAL_DECLARATIONS_H

#include "List.h"
#include <cstdint>
#include <MPU6050_tockn.h>
#include <Adafruit_BMP280.h>
#include <PID.h>
#include "Motor.h"

extern List serialBuffer;
extern HardwareSerial serial;

extern Adafruit_BMP280 bmp;
extern MPU6050 mpu;

extern PID PID_pitch_inner, PID_roll_inner, PID_yaw,
           PID_pitch_outer, PID_roll_outer;

extern Motor motor0, motor1, motor2, motor3;

#endif
