#pragma once

#include "core.h"

class AdrReg {
private:
    uint val = 0;
    uint MAX_VAL;
    char regCount;
public:
    AdrReg() { MAX_VAL = 2; }
    AdrReg(int registerCount) {
        regCount = registerCount;
        MAX_VAL = 2^(registerCount * 8)-1;
    }

    void add(Byte amt) {
        bool overflow = (MAX_VAL - val < 1);
        val += amt;
        if (overflow) val -= MAX_VAL;
    }

    void sub(Byte amt) {
        bool overflow = (val < 1);
        val -= amt;
        if (overflow) val += MAX_VAL;
    }

    void increment() { add(1); }
    void decrement() { sub(1); }

    uint getValue() { return val; }
    void setValue(const uint newVal) { val = newVal; }

    std::string toString() {
        std::string string = "Register Count: ";
        string + std::to_string((int) regCount);
        string + "   Val: ";
        string + std::to_string(val);
        return string;
    }
};
