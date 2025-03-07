#pragma once
#include "Bus.h"
#include "IInstructionController.h"
#include "Module.h"
#include <cstdint>
#include <initializer_list>
#define INSTRUCTION_WORD_LENGTH 64
#define STEP_SIZE 0b110+1  // Define the addressable bits and our count is plus 1 of the value of them all on // 7 steps

class InstructionController : public Module, public IInstructionController {
private:
    uint8_t currentStep;
    uint16_t storedInstruction;
    Bus* MainBus = nullptr;
    bool controlLines[INSTRUCTION_WORD_LENGTH]; // NOTE: This is sad space efficient because bools are dumb
    uint64_t instructionSet[0xFFFF+1][STEP_SIZE];

    bool* instructionRegisterIn = nullptr;
    bool* instructionRegisterOut = nullptr;

    void evaluateStep();
    void setupInstructionSet();
    void addInstruction(uint16_t instruction, std::initializer_list<uint64_t> steps);
    void addInstruction(uint16_t instructionLow, uint16_t instructionHigh, std::initializer_list<uint64_t> steps);
    void addInstruction(uint16_t instructionLow, uint16_t instructionHigh, std::initializer_list<uint64_t> steps, bool verbose);

    void performReset() override;
    void performClockHigh() override;
    void performClockLow() override;
    void performUpdateLines() override;

public:
    InstructionController(Bus& mainBus);

    void performConnectControlLines(IInstructionController &ptrIC) override;

    void LoadFromMainBus();
    void AssertToMainBus();
    void UnAssertToMainBus();

    /** Gets a pointer to the bool for the control line requested */
    virtual bool* GetControlLinePtr(ControlLines controlLine) override;
};
