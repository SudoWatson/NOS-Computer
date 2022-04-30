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
    RegisterController *RC = nullptr;
    ALU alu;

    CPU();

    ~CPU() { delete RC; }

    std::string toString();
};
