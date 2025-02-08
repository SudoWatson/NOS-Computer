#pragma once

class IInstructionController {
public:
    enum ControlLines {
        IRI = 1 << 0,  // Instruction Register In
        IRO = 1 << 1,  // Instructino Register Out
        RCI = 1 << 2,  // Register Controller In
        RI  = 1 << 3,  // Register In
        BRO = 1 << 4,  // Bypass Register Out
        EI  = 1 << 5,  // ALU Instruction In
        EO  = 1 << 6,  // ALU Out
    };

    /** Gets a pointer to the bool for the control line requested */
    virtual bool* GetControlLinePtr(ControlLines controlLine) = 0;
};
