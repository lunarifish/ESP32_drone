#include <Arduino.h>
#include "esp32-hal-cpu.h"

#include "Config.h"
#include "GlobalDeclarations.h"

#include <LEDUtils.h>
#include <MPU6050_tockn.h>
#include <Adafruit_BMP280.h>
#include "Motor.h"
#include <PID.h>
#include "SerialModule.h"

#include "TaskCycles.h"


bool debug_mode = true;
uint8_t curr;

LED led(2);

TwoWire I2C_BUS_0(0);
TwoWire I2C_BUS_1(1);
MPU6050 mpu(I2C_BUS_0);
Adafruit_BMP280 bmp(&I2C_BUS_1);

Motor motor0(0), motor1(1), motor2(2), motor3(3);

PID PID_pitch_inner(0.1, 700, -700, 2 , 0, 0),
    PID_roll_inner (0.1, 700, -700, 2 , 0, 0),
    PID_yaw        (0.1, 500, -500, 2 , 0, 0),
    PID_pitch_outer(0.1, 500, -500, 10, 0, 0),
    PID_roll_outer (0.1, 500, -500, 10, 0, 0);

void setup() {
    setCpuFrequencyMhz(240);
    Serial.begin(115200);

    // Initialize serial communication module
    // serialInit();
    

    // Initialize I2C devices (MPU6050, BMP280)
    // I2C_BUS_0.setPins(MPU6050_SDA_PIN, MPU6050_SCL_PIN);
    // I2C_BUS_1.setPins(BMP280_SDA_PIN, BMP280_SCL_PIN);
    //I2C_BUS_0.begin();
    // I2C_BUS_1.begin();
    // mpu.begin();
    // if (!bmp.begin(0x76)) {
    //     Serial.println("Barometer initialization failed");
    //     while (true);
    // }
    // mpu.calcGyroOffsets(true);


    // Initialize motors
    Serial.println("Initializing motors");
    Motor::initAll();
    motor0.arm();
    motor1.arm();
    motor2.arm();
    motor3.arm();
    
    // Flash! I'm done initialization lol
    led.blink(2, 100);


    // Create threads
    // xTaskCreatePinnedToCore(taskCycle1, "Thread-1", 10000, NULL, 1, NULL, 0);
    // xTaskCreatePinnedToCore(taskCycle2, "Thread-2", 10000, NULL, 1, NULL, 1);
    motor0.setThrottle(400);
    motor1.setThrottle(400);
    motor2.setThrottle(400);
    motor3.setThrottle(400);   
}

uint16_t i;
void loop() {
 
    // for (i = 200; i <= 400; i++) {
    //     motor0.setThrottle(i);
    //     motor1.setThrottle(i);
    //     motor2.setThrottle(i);
    //     motor3.setThrottle(i);
    // } 
    // for (i = 400; i >= 200; i--) {
    //     motor0.setThrottle(i);
    //     motor1.setThrottle(i);
    //     motor2.setThrottle(i);
    //     motor3.setThrottle(i);
    // }
    // led.blink(1, 80);

    // mpu.update();
    // Serial.println("init");
    // while (true){
    //     while (!serial.available());
    //     Serial.println(serial.read());
    // }


    // Serial.print(mpu.getGyroX());Serial.print(" ");
    // Serial.print(mpu.getGyroY());Serial.print(" ");
    // Serial.println(mpu.getGyroZ());
    // serialBuffer.clear();
    // serialReadIntoBuffer();
    // for (uint8_t item : serialBuffer) {
    //     Serial.print(item);
    //     Serial.print(" ");
    // }
    // Serial.println(serialBuffer.size());

    // mpu.update();
    // Serial.print("BMP280: ");
    // Serial.print(bmp.readTemperature());
    // Serial.print("Ce  ");
    // Serial.print("MPU6050: ");
    // Serial.print(mpu.getTemp());
    // Serial.println("Ce");


    // mpu.update();
    // eulerAngles[0] = mpu.getAngleX();
    // eulerAngles[1] = mpu.getAngleY();
    // eulerAngles[2] = mpu.getAngleZ();

    // Serial.print((int16_t)(eulerAngles[0] * 10)); Serial.print(" ");
    // Serial.print((int16_t)(eulerAngles[1] * 10)); Serial.print(" ");
    // Serial.print((int16_t)(eulerAngles[2] * 10)); Serial.print(" ");

    // writeByteArray(PACKET_HEADER, 2);
    // writeInt16((int16_t)(eulerAngles[0] * 10));
    // writeInt16((int16_t)(eulerAngles[1] * 10));
    // writeInt16((int16_t)(eulerAngles[2] * 10));
    // writeByteArray(PACKET_TAIL, 2);
}