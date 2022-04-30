#pragma once

#include "core.h"

class Reg {
private:
    Byte val = 0;
    uint MAX_VAL = 0xFF;
public:

    // TODO Add flag setting on these only maybe

    void add(Byte amt) {
        bool overflow = (MAX_VAL - val < 1);
        val += amt;
    }

    void sub(Byte amt) {
        bool overflow = (val < 1);
        val -= amt;
    }

    void increment() { add(1); }
    void decrement() { sub(1); }

    Byte getValue() { return val; }
    void setValue(const Byte newVal) { val = newVal; }

    Reg operator&(const Reg reg) {
        Reg newReg = Reg();
        newReg.val = (val & reg.val);
        return newReg;
    }

    Reg operator|(const Reg reg) {
        Reg newReg = Reg();
        newReg.val = (val | reg.val);
        return newReg;
    }

    Reg operator^(const Reg reg) {
        Reg newReg = Reg();
        newReg.val = (val ^ reg.val);
        return newReg;
    }

    Reg operator~() {
        Reg newReg = Reg();
        newReg.val = (~val);
        return newReg;
    }

    Reg operator+(const Reg reg) {
        Reg newReg = Reg();
        newReg.val = (val + reg.val);
        return newReg;
    }

    Reg operator-(const Reg reg) {
        Reg newReg = Reg();
        newReg.val = (val - reg.val);
        return newReg;
    }

    Reg operator=(const Reg reg) {
        Reg newReg = Reg();
        newReg.val = reg.val;
        return newReg;
    }

    std::string toString() {
        std::string string = "Value: ";
        string + std::to_string((int) val);
        return string;
    }

};
