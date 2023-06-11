#pragma once

#ifndef _LIST_H
#define _LIST_H

#include <cstdint>

class List {
public:
    void     append(uint8_t item);
    void     remove(uint8_t index);
    void     clear();
    uint8_t  size();
    uint8_t* getArray();
    uint8_t* begin();
    uint8_t* end();
    bool     empty();
private:
    uint8_t  length;
    uint8_t  data[16];
};

#endif