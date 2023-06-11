#pragma once

#ifndef SERIALPACKET_H
#define SERIALPACKET_H

#include <cstdint>


// Packet types
const uint8_t STA_HEARTBEAT      = 0x30;
const uint8_t STA_CTRL           = 0x31;
const uint8_t STA_INSTR          = 0x32;


// STA_INSTR instructions
const uint8_t MOTOR_ARM          = 0xf1;
const uint8_t MOTOR_DISARM       = 0xf2;
const uint8_t MOTOR_SET_THROTTLE = 0xf3;


#endif