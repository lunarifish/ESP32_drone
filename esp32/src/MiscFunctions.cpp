#include "MiscFunctions.h"

#include "Config.h"
#include "GlobalDeclarations.h"


void initI2CDevices() {
    // Initialize I2C devices (MPU6050, BMP280)
    I2C_BUS_0.setPins(MPU6050_SDA_PIN, MPU6050_SCL_PIN);
    I2C_BUS_1.setPins(BMP280_SDA_PIN, BMP280_SCL_PIN);
    I2C_BUS_0.begin();
    I2C_BUS_1.begin();

    mpu.begin();
    if (!bmp.begin(0x76)) {
        Serial.println("Barometer initialization failed");
        while (true);
    }
    mpu.calcGyroOffsets(true);
}