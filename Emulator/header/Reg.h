#pragma once

#include "core.h"

class Reg {
private:
    Byte val = 0;
    uint MAX_VAL = 0xFF;
public:

    // TODO Add flag setting on these only maybe

    void add(Byte amt);
    void sub(Byte amt);

    void increment() { add(1); }
    void decrement() { sub(1); }

    Byte getValue() { return val; }
    void setValue(const Byte newVal) { val = newVal; }

    Reg operator&(const Reg reg);
    Reg operator|(const Reg reg);
    Reg operator^(const Reg reg);
    Reg operator~();
    Reg operator+(const Reg reg);
    Reg operator-(const Reg reg);
    void operator=(const Reg reg);
    std::string toString();

};
