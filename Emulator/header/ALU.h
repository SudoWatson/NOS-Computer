#pragma once

#include "core.h"
#include "Reg.h"

class CPU;

class ALU {
    Byte inst;

    CPU *pCPU;

public:
    Reg *LHR;  // Left-Hand Register
    Reg *RHR;  // Right-Hand Register
    Reg *OPR;  // Output Register

    ALU() {}
    ALU(CPU *cpu);

    void loadInstruction(Byte instruction) {inst = instruction; }

    void execute();

};
