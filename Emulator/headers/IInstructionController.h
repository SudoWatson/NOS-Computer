#pragma once

class IInstructionController {
public:
    enum ControlLines {
        IRI = 1 << 0,  // Instruction Register In
        IRO = 1 << 1,  // Instructino Register Out
        RCI = 1 << 2,  // Register Controller In
        SI1 = 1 << 3,  // Register Controller SPR Index 1
        SI2 = 1 << 4,  // Register Controller SPR Index 2
        SRE = 1 << 5,  // Register Controller Enable SPR instead
        SO1 = 1 << 6,  // Register Controller SPR Out Index 1
        SO2 = 1 << 7,  // Register Controller SPR Out Index 1
        RI  = 1 << 8,  // Register In
        BRO = 1 << 9,  // Bypass Register Out
        EI  = 1 << 10,  // ALU Instruction In
        EO  = 1 << 11,  // ALU Out
    };

    /** Gets a pointer to the bool for the control line requested */
    virtual bool* GetControlLinePtr(ControlLines controlLine) = 0;
};
