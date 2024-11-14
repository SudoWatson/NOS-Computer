#pragma once
#include "Bus.h"
#include "IInstructionController.h"
#include "Module.h"
#include <cstdint>
#include <initializer_list>
#define INSTRUCTION_WORD_LENGTH 16
#define STEP_SIZE 0b1111

class InstructionController : Module, IInstructionController {
private:
    uint8_t currentStep;
    uint16_t storedInstruction;
    Bus* MainBus;
    bool controlLines[INSTRUCTION_WORD_LENGTH]; // NOTE: This is sad space efficient because bools are dumb
    uint64_t instructionSet[0xFFFF][STEP_SIZE];

    bool* instructionRegisterIn;
    bool* instructionRegisterOut;

    void evaluateStep();
    void setupInstructionSet();
    void addInstruction(uint16_t instruction, std::initializer_list<uint64_t> steps);
    void addInstruction(uint16_t instructionLow, uint16_t instructionHigh, std::initializer_list<uint64_t> steps);

public:


    InstructionController(Bus& mainBus);

    void performReset() override;
    void performClockHigh() override;
    void performClockLow() override;
    void performUpdateLines() override;

    void performRegisterControlLines(IInstructionController &ptrIC) override;

    void LoadFromMainBus();
    void AssertToMainBus();
    void UnAssertToMainBus();

    /** Gets a pointer to the bool for the control line requested */
    bool* GetControlLinePtr(ControlLines controlLine) override;
};
