#pragma once

#include "core.h"
#include "Reg.h"
#include "RegisterController.h"
#include "ALU.h"
#include "AdrReg.h"


class CPU {
public:
    AdrReg PC;
    AdrReg MAR;
    Reg Inst;
    RegisterController RC;
    ALU alu;

    CPU();

    std::string toString();

    void execute(Byte instruction);
};
