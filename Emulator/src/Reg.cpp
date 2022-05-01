#include "Reg.h"


void Reg::add(Byte amt) {
    bool overflow = (MAX_VAL - val < 1);
    val += amt;
}

void Reg::sub(Byte amt) {
    bool overflow = (val < 1);
    val -= amt;
}



Reg Reg::operator&(const Reg reg) {
    Reg newReg = Reg();
    newReg.val = (val & reg.val);
    return newReg;
}

Reg Reg::operator|(const Reg reg) {
    Reg newReg = Reg();
    newReg.val = (val | reg.val);
    return newReg;
}

Reg Reg::operator^(const Reg reg) {
    Reg newReg = Reg();
    newReg.val = (val ^ reg.val);
    return newReg;
}

Reg Reg::operator~() {
    Reg newReg = Reg();
    newReg.val = (~val);
    return newReg;
}

Reg Reg::operator+(const Reg reg) {
    Reg newReg = Reg();
    newReg.val = (val + reg.val);
    return newReg;
}

Reg Reg::operator-(const Reg reg) {
    Reg newReg = Reg();
    newReg.val = (val - reg.val);
    return newReg;
}

void Reg::operator=(const Reg reg) {
    val = reg.val;
}

std::string Reg::toString() {
    std::string string = "Value: ";
    string += std::to_string((int) val);
    return string;
}