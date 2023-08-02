#pragma once

#ifndef COMMMODULE_H
#define COMMMODULE_H

#include <HardwareSerial.h>
#include "CommPacket.h"
#include "List.h"

void commInit();
void commReadIntoBuffer();
void writeInt16(int16_t num);
void writeByteArray(uint8_t* arr, uint8_t length);

#endif