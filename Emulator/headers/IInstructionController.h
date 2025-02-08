#pragma once

class IInstructionController {
public:
    enum ControlLines {
        IRI = 1 << 0,  // Instruction Register In
        IRO = 1 << 1,  // Instructino Register Out
        RCI = 1 << 2,  // Register Controller In
        RI  = 1 << 3,  // Register In
        EI  = 1 << 4,  // ALU Instruction In
        EO  = 1 << 5,  // ALU Out
        BRO = 1 << 6,  // Bypass Register Out
    };

    /** Gets a pointer to the bool for the control line requested */
    virtual bool* GetControlLinePtr(ControlLines controlLine) = 0;
};
