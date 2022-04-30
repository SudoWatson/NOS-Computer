#pragma once

#include "core.h"

#include "Reg.h"
//#include "CPU.h"
class CPU;

class RegisterController {
public:
    CPU *pCPU = nullptr;

    Byte RegSelection = 0;

    Reg AReg;
    Reg BReg;
    Reg CReg;
    Reg DReg;
    RegisterController(CPU *cpu);

    Reg *getRegister(const Byte selection);

    void RCIn(Byte selection);

    std::string toString();

};
