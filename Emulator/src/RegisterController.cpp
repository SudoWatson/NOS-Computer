#include "RegisterController.h"

RegisterController::RegisterController(CPU *cpu) {
    pCPU = cpu;
    AReg = Reg();
    BReg = Reg();
    CReg = Reg();
    DReg = Reg();
}

Reg *RegisterController::getRegister(const Byte selection) {
    Byte i = 0b11 & selection;
    switch (i)
    {
    case 0b00:
        return &AReg;
        break;
    case 0b01:
        return &BReg;
        break;
    case 0b10:
        return &CReg;
        break;
    case 0b11:
        return &DReg;
        break;
    default:
        return nullptr;
    }
}

void RegisterController::RCIn(Byte selection) {
    RegSelection = selection;

    // pCPU->alu.OPR = getRegister(RegSelection >> 0);
    // pCPU->alu.RHR = getRegister(RegSelection >> 2);
    // pCPU->alu.LHR = getRegister(RegSelection >> 4);
}

std::string RegisterController::toString() {
    std::string string = "--REGISTERS--\n";
    string += "A: " + AReg.toString() + "\n";
    string += "B: " + BReg.toString() + "\n";
    string += "C: " + CReg.toString() + "\n";
    string += "D: " + DReg.toString() + "\n";
    return string;
}
