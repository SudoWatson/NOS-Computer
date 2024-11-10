#pragma once
#include "Bus.h"
#include <cstdint>
#define INSTRUCTION_WORD_LENGTH 16
#define STEP_SIZE 16

class InstructionController {
    uint8_t currentStep;
    uint16_t storedInstruction;
    Bus* MainBus;
    bool controlLines[INSTRUCTION_WORD_LENGTH]; // NOTE: This is sad space efficient because bools are dumb
    uint64_t instructionSet[0xFFFF][STEP_SIZE];

    bool* loadEnable;

    void evaluateStep();
    /**
     * After all the lines are updated, this will notify any module so it can do what it needs
     * EX: Assert to bus. Actually that could be problematic, might need a couple of these
     *  to do Unassert to Buses, then Assert to Busses
    */
    void alertLinesUpdated();
public:
    enum Instructions : char {
        RI = 0, // Right-most bit of word
        RII,
        RIO,
        IRI,
        EO
    };

    void Clock();
    InstructionController(Bus& mainBus);
    void LoadFromMainBus();
    void AssertToMainBus();

    void UnAssertToMainBus();
    bool* GetInstructionPtr(Instructions inst);
};
