#include <HardwareSerial.h>
#include "Config.h"
#include "CommModule.h"
#include "List.h"


HardwareSerial serial(1);
List serialBuffer;


void commInit() {
    serial = HardwareSerial(1);

    serial.begin(AS69_BAUDRATE, SERIAL_8N1, AS69_TX_PIN, AS69_RX_PIN);
    serialBuffer.clear();

    pinMode(AS69_MD0_PIN, OUTPUT);
    pinMode(AS69_MD1_PIN, OUTPUT);
    pinMode(AS69_AUX_PIN, INPUT);

    // Wait for comm module initialization
    if (digitalRead(AS69_AUX_PIN) == LOW) {
        Serial.println("Radio initiating");
        while(digitalRead(AS69_AUX_PIN) == LOW);
        Serial.println("Radio initialized");
    }

    // Set module to normal mode
    digitalWrite(AS69_MD0_PIN, HIGH);
    digitalWrite(AS69_MD1_PIN, LOW);
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


void decodeMsg(uint8_t msg) {
    /***
     * A FSM algorithm that handles the data stream
     * coming from controller(ground station)
    **/

}