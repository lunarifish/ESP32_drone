#pragma once

#ifndef SERIALMODULE_H
#define SERIALMODULE_H

#include <HardwareSerial.h>
#include "SerialPacket.h"
#include "List.h"

void serialInit();
void serialReadIntoBuffer();
void writeInt16(int16_t num);
void writeByteArray(uint8_t* arr, uint8_t length);

#endif