#include "AdrReg.h"

AdrReg::AdrReg(int registerCount) {
    regCount = registerCount;
    MAX_VAL = 2^(registerCount * 8)-1;
}

void AdrReg::add(Byte amt) {
    bool overflow = (MAX_VAL - val < 1);
    val += amt;
    if (overflow) val -= MAX_VAL;
}

void AdrReg::sub(Byte amt) {
    bool overflow = (val < 1);
    val -= amt;
    if (overflow) val += MAX_VAL;
}

std::string AdrReg::toString() {
    std::string string = "BitCount: ";
    string += std::to_string((int) regCount * 8);
    string += "   Val: ";
    string += std::to_string(val);
    return string;
}