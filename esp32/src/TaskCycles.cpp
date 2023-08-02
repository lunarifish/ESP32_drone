#include "TaskCycles.h"
#include "CommModule.h"
#include "GlobalDeclarations.h"


// Thread 1 variables
int16_t pid_pitch_outer_output, pid_roll_outer_output,
        pid_pitch_output, pid_roll_output, pid_yaw_output;
int16_t motor0_offset, motor1_offset, motor2_offset, motor3_offset;
bool thread1_pause = false;


// Thread 2 variables
enum ReaderState {header = 0, type, payload}
        reader_state = header;
uint8_t current_byte, countdown, packet_type;
uint16_t ref_throttle, pitch, roll, yaw;
uint8_t packet_datalen[33] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                              0, 8, 1};
uint8_t decoder_buffer[8] = {0,0,0,0,0,0,0,0};
bool first_0xff = false;


/**
 * @paragraph Thread 1 task list
 * 
 * 1. Read sensors
 *   (1) MPU6050 - Pitch, Roll, Yaw angular velocity
 *   (2) BMP280  - Altitude, Temperature
 * 2. Calculate PIDs
 *   (1) Attitude
 *   (2) Altitude
 * 3. Apply adjustments to motors
 * 
 * @param parameter Taskfunction_t
 */

void taskCycle1(void* parameter) {
    while (true) {
        mpu.update();

        pid_pitch_outer_output = PID_pitch_outer.calculate(0, mpu.getAngleX());
        pid_roll_outer_output = PID_roll_outer.calculate(0, mpu.getAngleY());
        pid_pitch_output = PID_pitch_inner.calculate(pid_pitch_outer_output, mpu.getGyroX());
        pid_roll_output = PID_pitch_inner.calculate(pid_roll_outer_output, mpu.getGyroY());
        pid_yaw_output = PID_yaw.calculate(0, mpu.getGyroZ());

        motor0_offset = - pid_pitch_output + pid_roll_output - pid_yaw_output;
        motor1_offset = - pid_pitch_output - pid_roll_output + pid_yaw_output;
        motor2_offset =   pid_pitch_output - pid_roll_output - pid_yaw_output;
        motor3_offset =   pid_pitch_output + pid_roll_output + pid_yaw_output;

        motor0.setThrottle(motor0.getReferenceThrottle() + motor0_offset);
        motor1.setThrottle(motor1.getReferenceThrottle() + motor1_offset);
        motor2.setThrottle(motor2.getReferenceThrottle() + motor2_offset);
        motor3.setThrottle(motor3.getReferenceThrottle() + motor3_offset);


        // Serial.print(pid_pitch_output); Serial.print(" ");
        // Serial.print(pid_roll_output); Serial.println(" ");


        // Serial.print(motor0_offset); Serial.print(" ");
        // Serial.print(motor1_offset); Serial.print(" ");
        // Serial.print(motor2_offset); Serial.print(" ");
        // Serial.print(motor3_offset); Serial.print(" | ");
        // Serial.print(motor0.getReferenceThrottle() + motor0_offset); Serial.print(" ");
        // Serial.print(motor1.getReferenceThrottle() + motor1_offset); Serial.print(" ");
        // Serial.print(motor2.getReferenceThrottle() + motor2_offset); Serial.print(" ");
        // Serial.print(motor3.getReferenceThrottle() + motor3_offset); Serial.print(" | ");
        // Serial.print(motor0.getThrottle()); Serial.print(" ");
        // Serial.print(motor1.getThrottle()); Serial.print(" ");
        // Serial.print(motor2.getThrottle()); Serial.print(" ");
        // Serial.print(motor3.getThrottle()); Serial.println("");
        while (thread1_pause);
    }
}


/**
 * Thread 2 task list
 * 
 * 1. Read serial port
 * 2. Parse packet
 *
 */

void taskCycle2(void* parameter) {
    reader_state = header;
    while (true) {
        while (serial.available() == 0);
        current_byte = serial.read();
        // Serial.println(current_byte);

        switch(reader_state) {
        case header:
            if (current_byte == 0xff) {
                if(first_0xff) {
                    first_0xff = false;
                    reader_state = type;
                    // Serial.println("TYPE start");
                } else
                    first_0xff = true;
            } else {
                if(first_0xff)
                    first_0xff = false;
            }
            break;
        case type:
            if(current_byte < 0x30 || current_byte > 0x34) {
                reader_state = header;
                //TODO: report corrupted packet
                Serial.println("Received corrupted packet: Wrong type");
                break;
            } else
                countdown = packet_datalen[current_byte];
            if (current_byte == STA_HEARTBEAT){
                reader_state = header;
                decodeBuffer(STA_HEARTBEAT);
            }
            else {
                // Serial.println("PAYLOAD start");
                reader_state = payload;
                packet_type = current_byte;
                //TODO: decoder
            }
            break;
        case payload:
            // Serial.print("Payload countdown=");
            // Serial.println(countdown);
            if(current_byte == 0xff) {
                if(countdown == 1) {
                    reader_state = header;
                    first_0xff = false;
                    //TODO: report corrupted packet
                    Serial.println("Received corrupted packet: 0xff at end of the packet");
                    break;
                }
                if(first_0xff) {
                    first_0xff = false;
                    reader_state = header;
                    //TODO: report corrupted packet
                    Serial.println("Received corrupted packet: double 0xff in payload");
                    break;
                }
            } else {
                    if(first_0xff)
                        first_0xff = false;
            }
            countdown--;
            decoder_buffer[countdown] = current_byte;
            if(countdown == 0) {
                // Serial.println("decoding");
                decodeBuffer(packet_type);
                reader_state = header;
            }
            break;
        default:
            ;
        }
    }
}


void decodeBuffer(uint8_t packet_type) {
    switch (packet_type) {
    case STA_HEARTBEAT:
        Serial.println("Received STA_HEARTBEAT");
        break;
    case STA_CTRL:
        ref_throttle = decoder_buffer[6] + decoder_buffer[7] << 8;
        pitch = decoder_buffer[4] + decoder_buffer[5] << 8;
        roll = decoder_buffer[2] + decoder_buffer[3] << 8;
        yaw = decoder_buffer[0] + decoder_buffer[1] << 8;
        Serial.print("Received STA_CTRL: ");
        Serial.print(ref_throttle); Serial.print(" ");
        Serial.print(pitch); Serial.print(" ");
        Serial.print(roll); Serial.print(" ");
        Serial.print(yaw); Serial.println(" ");
        break;
    case STA_INSTR:
        Serial.print("Received STA_INSTR: ");
        Serial.println(decoder_buffer[7]);
        break;
    default:
        ;
    }
}