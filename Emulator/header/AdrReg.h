#pragma once

#include "core.h"

class AdrReg {
private:
    uint val = 0;
    uint MAX_VAL;
    char regCount;
public:
    AdrReg() {}
    AdrReg(int registerCount);
    

    void add(Byte amt);

    void sub(Byte amt);

    void increment() { add(1); }
    void decrement() { sub(1); }

    uint getValue() { return val; }
    void setValue(const uint newVal) { val = newVal; }

    std::string toString();
};
