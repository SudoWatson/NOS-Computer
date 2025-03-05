#pragma once

#include <cstdint>
#include <bits/stdc++.h>

class IInstructionController {
public:
    enum ControlLines {
        IRI = 1 << 0,  // Instruction Register In
        IRO = 1 << 1,  // Instructino Register Out
        RCI = 1 << 2,  // Register Controller In - Might be able to just always do this in the fetch cycle
        SI1 = 1 << 3,  // Register Controller SPR Index 1
        SI2 = 1 << 4,  // Register Controller SPR Index 2
        SRE = 1 << 5,  // Register Controller Enable SPR instead
        SO1 = 1 << 6,  // Register Controller SPR Out Index 1
        SO2 = 1 << 7,  // Register Controller SPR Out Index 1
        RI  = 1 << 8,  // Register In
        BRO = 1 << 9,  // Bypass Register Out - Needs EO at same time
        EI  = 1 << 10,  // ALU Instruction In
        EO  = 1 << 11,  // ALU Out
        RMI = 1 << 12,  // RAM In
        RMO = 1 << 13,  // RAM Out
    };

    const uint16_t MAR = SRE;             // Memory Address Register Enable
    const uint16_t PCE = SRE | SI1;       // Program Counter Enable
    const uint16_t SPE = SRE | SI2;       // Stack Pointer Enable
    const uint16_t IDKE= SRE | SI1 | SI2; // IDK yet Register Enable

    const uint16_t PCO = SO1;             // Program Counter Enable
    const uint16_t SPO = SO2;             // Stack Pointer Enable
    const uint16_t IDKO= SO1 | SO2;       // IDK yet Register Enable

    const uint16_t FETCH1 = PCO | MAR | RI;  // First step in fetch cycle
    const uint16_t FETCH2 = /*RAMO |*/ IRI;  // Second step in fetch cycle

    /** Gets a pointer to the bool for the control line requested */
    virtual bool* GetControlLinePtr(ControlLines controlLine) = 0;
};
