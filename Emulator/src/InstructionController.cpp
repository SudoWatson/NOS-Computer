#include "../headers/InstructionController.h"
#include "IInstructionController.h"
#include <cstdint>
#include <bits/stdc++.h>
#include <iostream>
#include <ostream>
#define IC InstructionController

IC::InstructionController(Bus& mainBus) {
    MainBus = &mainBus;

    for (int i = 0; i < sizeof(controlLines)/sizeof(*controlLines); i++) {
        controlLines[i] = false;
    }

    setupInstructionSet();
}

void IC::LoadFromMainBus() {
    storedInstruction = *MainBus->GetValue();
    evaluateStep();
}

void IC::AssertToMainBus() {
    MainBus->Assert(&storedInstruction);
}

void IC::UnAssertToMainBus() {
    MainBus->UnAssert(&storedInstruction);
}

bool* IC::GetControlLinePtr(ControlLines controlLine) {
    int index = (int) log2(controlLine);  // Gets the index of the 1 bit in a 64 bit word
    return &controlLines[index];
}

void IC::performConnectControlLines(IInstructionController &ptrIC) {
    instructionRegisterIn = ptrIC.GetControlLinePtr(ptrIC.IRI);
    instructionRegisterOut = ptrIC.GetControlLinePtr(ptrIC.IRO);
}

void IC::evaluateStep() {
    uint64_t microinstruction = instructionSet[storedInstruction][currentStep];
    for (int i = 0; i < INSTRUCTION_WORD_LENGTH; i++) {
        controlLines[i] = (microinstruction >> i) & 1;
    }
}

void IC::performClockHigh() {
    if (*instructionRegisterIn) {
        LoadFromMainBus();
    }
}

void IC::performClockLow() {
    currentStep++;
    if (currentStep >= STEP_SIZE)
    {
        currentStep = 0;
    }
    evaluateStep();
}

void IC::performReset() {
    currentStep = 0;
    storedInstruction = 0;
    evaluateStep();
}

void IC::performUpdateLines() {
    if (*instructionRegisterOut) {
        AssertToMainBus();
    } else {
        UnAssertToMainBus();
    }
}

void IC::addInstruction(uint16_t instruction, std::initializer_list<uint64_t> steps) {
    addInstruction(instruction, instruction, steps);
}
void IC::addInstruction(uint16_t instructionLow, uint16_t instructionHigh, std::initializer_list<uint64_t> steps) {
    for (; instructionLow <= instructionHigh; instructionLow++) {
        int stepIndex = 0;
        instructionSet[instructionLow][stepIndex++] = FETCH1;
        instructionSet[instructionLow][stepIndex++] = FETCH2;
        for (auto& step : steps) {
            instructionSet[instructionLow][stepIndex++] = step;
        }
        if (instructionLow == 0xFFFF) // Will overflow and never get higher than max instructionHigh
        {
            break;
        }
    }
}

void IC::setupInstructionSet() {
    // NOP in all spaces by default
    addInstruction(0x0000, 0xFFFF, {0});


    // Load SPR 00
    // 000   00XX
    //

    addInstruction(0x0000, { SRE | RI  });
    addInstruction(0x0001, { SRE | SI1 | RI  });
    addInstruction(0x0002, { SRE | SI2 | RI  });
    addInstruction(0x0003, { SRE | SI1 | SI2 | RI  });

    addInstruction(0x0004, { SO1 | SRE | SI1 | SI2 | RI });
    addInstruction(0x0005, { SO2 | SRE | SI1 | SI2 | RI });
    addInstruction(0x0006, { SO1 | SO2 | SRE | SI1 | RI });


    // Move register to register
    //
}

