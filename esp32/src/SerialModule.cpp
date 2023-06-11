#include <HardwareSerial.h>
#include "Config.h"
#include "SerialModule.h"
#include "List.h"


HardwareSerial serial(1);
List serialBuffer;

void serialInit() {
    serial = HardwareSerial(1);

    serial.begin(SERIAL_BAUDRATE, SERIAL_8N1, SERIAL_RX_PIN, SERIAL_TX_PIN);
    serialBuffer.clear();

    pinMode(SERIAL_MD0_PIN, OUTPUT);
    pinMode(SERIAL_MD1_PIN, OUTPUT);
    pinMode(SERIAL_AUX_PIN, INPUT);

    // Wait for serial module to initialize
    if (digitalRead(SERIAL_AUX_PIN) == LOW) {
        Serial.println("Radio initiating");
        while(digitalRead(SERIAL_AUX_PIN) == LOW);
        Serial.println("Radio initialized");
    }
        
    // Set work mode to normal mode
    digitalWrite(SERIAL_MD0_PIN, HIGH);
    digitalWrite(SERIAL_MD1_PIN, LOW);
}

void writeU16(int16_t num) {
    // convert uint16 to bytearray
    serial.write(num);
    serial.write(num >> 8);
}

void writeByteArray(uint8_t* arr, uint8_t length) {
    for (int i = 0; i < length; i++) {
        serial.write(arr[i]);
    }
}