#include "List.h"
#include <cstring>
#include <cstdint>

void List::append(uint8_t item) {
    if (length < 16)
        data[length++] = item;
}

void List::remove(uint8_t index) {
    if (index >= length)
        return;
    memmove(&data[index], &data[index+1], length - index - 1);
    length--;
}

void List::clear() {
    memset(data, 0, 16);
    length = 0;
}

uint8_t List::size() {
    return length;
}

uint8_t* List::begin() {
    return data;
}

uint8_t* List::end() {
    return data + length;
}

uint8_t* List::getArray() {
    return data;
}

bool List::empty() {
    return length == 0 ? true : false;
}