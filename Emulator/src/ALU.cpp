#include "ALU.h"


ALU::ALU(CPU *cpu) {
    pCPU = cpu;
}


void ALU::execute() {
    // TODO More switch casing
    if (!((0b1000 & inst) >> 3)) {  // If first bit of last nibble is 0, deal with arithmetic
    // TODO Handle carry and other flags
        if (!((0b10 & inst) >> 1)) {  // Add
            *OPR = *LHR + *RHR;
        } else {  // Subtract
            *OPR = *LHR - *RHR;
        }
    } else {  // If first bit of last nibble is 1, logic
        switch ((0b0110 & inst) >> 1)  // Get just 0000 0XX0
        {
        case 0b00:
            // AND
            *OPR = *LHR & *RHR;
            break;
        case 0b01:
            // OR
            *OPR = *LHR | *RHR;
            break;
        case 0b10:
            // XOR
            *OPR = *LHR ^ *RHR;
            break;
        default:
            // Unknown command
            break;
        }
        if (0b1 & inst) *OPR = ~*OPR;  // NOT
    }
}