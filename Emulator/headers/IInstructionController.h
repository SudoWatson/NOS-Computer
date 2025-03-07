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
        INC = 1 << 14,  // Increment
        DEC = 1 << 15,  // Decrement
    };

    /* TODO: Need to specialize Special Purpose Register
     * I'm trying to generalize the SPRs but that's getting me into some annoying issues of not having full control over them
     * I should just treat them as they are, special. They are SPECIAL Purpose Registers, not General
     * I need to remove all of the current SPR relating Control Lines
     * I instead need to have individual control lines for the actions of that specific SPR.
     * Not every SPR has all the same actions. EX: MAR just loads. PC doesn't decrement. SP does it all.
     * This will allow me to control multiple SPRs at once as well, such as loading the IR while INC the PC
     * Or INC PC while doing a regular register operation to do instructions in time faster
     */
    const uint64_t MAR = SRE;             // Memory Address Register Enable
    const uint64_t PCE = SRE | SI1;       // Program Counter Enable
    const uint64_t SPE = SRE | SI2;       // Stack Pointer Enable
    const uint64_t IDKE= SRE | SI1 | SI2; // IDK yet Register Enable

    const uint64_t PCO = SO1;             // Program Counter Enable
    const uint64_t SPO = SO2;             // Stack Pointer Enable
    const uint64_t IDKO= SO1 | SO2;       // IDK yet Register Enable

    const uint64_t FETCH1 = PCO | MAR | RI;  // First step in fetch cycle
    const uint64_t FETCH2 = RMO | IRI | PCE | INC;       // Second step in fetch cycle

    /** Gets a pointer to the bool for the control line requested */
    virtual bool* GetControlLinePtr(ControlLines controlLine) = 0;
};
