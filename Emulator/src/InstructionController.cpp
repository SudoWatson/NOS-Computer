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

uint8_t IC::readCurrentStep()
{
    return currentStep;
}

uint16_t IC::readCurrentInstruction()
{
    return storedInstruction;
}

void IC::addInstruction(uint16_t instruction, std::initializer_list<uint64_t> steps) {
    addInstruction(instruction, instruction, steps);
}
void IC::addInstruction(uint16_t instructionLow, uint16_t instructionHigh, std::initializer_list<uint64_t> steps) {
    addInstruction(instructionLow, instructionHigh, steps, true);
}
void IC::addInstruction(uint16_t instructionLow, uint16_t instructionHigh, std::initializer_list<uint64_t> steps, bool verbose) {
    if (instructionLow > instructionHigh)
    {
        std::cout << "Attempting to fill addresses " << instructionLow << " - " << instructionHigh << ", but the high address comes before the low address" << std::endl;
        return;
    }
    for (; instructionLow <= instructionHigh; instructionLow++) {
        int stepIndex = 0;
        instructionSet[instructionLow][stepIndex++] = FETCH1;
        instructionSet[instructionLow][stepIndex++] = FETCH2;
        for (auto& step : steps) {
            if (verbose && (instructionSet[instructionLow][stepIndex] != 0ULL) && (stepIndex != 0) && (stepIndex != 1))
            {
                std::cout << "Overlapping instructions at address " << instructionLow << " step #" << stepIndex << ". Original instruction: " << instructionSet[instructionLow][stepIndex] << "  Overriding Instruction: " << step << std::endl;
            }
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
    addInstruction(0x0000, 0xFFFF, {0, 0, 0, 0, 0}, false);

    // Load SPR 00
    // 000   00XX
    //

    //                   Index register  MAR in     Register into ram
    addInstruction(0x0000, 0x3FFF, { IRO | RCI, EO | RI, 0, 0, 0 }); // Arithmetic
    //addInstruction(0x4000, 0x7FFF, { IRO | RCI, EO | RI, 0, 0, 0 }); // Free space!
    // TODO: More stuff is needing for flag jumping
    addInstruction(0x4000, 0x43FF, { IRO /* |FlagRegIn*/ | MAR | INC, RMO | RCI | PCE | INC, EO | RI, EO | BRO | PCE | RI /* Flag test */, 0 }); // JMP Indexed - Next memory location is register controller instruction of registers to add together for location -  NOTE: Will need the result (enabled) register to be the same as the Right Hand register, as it will be outputting it's result on the bus
    addInstruction(0x4400, 0x47FF, { IRO /* |FlagRegIn*/ | MAR | INC, RMO | MAR | RI, RMO | PCE | RI /* Flag test */, 0, 0 }); // JMP Addressed - Next memory address is address of stored jump address location
    addInstruction(0x4800, 0x4BFF, { IRO /* |FlagRegIn*/ | MAR | INC, RMO | RCI | PCE | INC, EO | BRO | PCE | RI /* Flag test */, 0, 0 }); // JMP Register - Next memory location is register controller instruction of register to output for stored address
    addInstruction(0x4C00, 0x4FFF, { IRO /* |FlagRegIn*/ | MAR | INC, RMO | PCE | RI /* Flag test */, 0, 0, 0 }); // JMP Immediate -- 0100 00MM MMMF FFFF - MMMMM: Mask select which flags to test on FFFFF: Value those flags must match - PC Load
    // 01xx xxMM MMMF FFFF
    addInstruction(0x8000, 0x88FF, { IRO | RCI, EO | RI, 0, 0, 0 }); // Shift + Bitwise Passthrough
    addInstruction(0x9000, 0xB888, { IRO | RCI, EO | RI, 0, 0, 0 }); // Bitwise pt 1
    addInstruction(0xC000, 0xC0FF, { IRO | RCI, EO | BRO | RI, 0, 0, 0 }); // GPR to GPR
    // addInstruction(0xC000, 0xC0FF, { IRO | RCI, EO | BRO | RI, 0, 0, 0 }); // GPR to SPR
    // addInstruction(0xC400, 0xC40F, {  }); // SPR to GPR
    // addInstruction(0xC000, 0xC888, {  }); // SPR to SPR
    addInstruction(0xC400, 0xC40F, { IRO | RCI | MAR | INC, RMO | RI, PCE | INC, 0, 0 }); // GPR Immediate Load
    addInstruction(0xC410, 0xC41F, { IRO | RCI | MAR | INC, RMO | MAR | RI, RMO | RI, PCE | INC, 0}); // GPR Addressed Load
    // addInstruction(0xC000, 0xC00F, {  }); // SPR immediate load
    // addInstruction(0xC000, 0xC00F, {  }); // SPR Addressed Load
    addInstruction(0xC440, 0xC44F, { IRO | RCI | MAR | INC, RMO | MAR | RI, EO | BRO | RMI | PCE | INC, 0, 0 }); // Store GPR
    // addInstruction(0xC000, 0xC00F, {  }); // Store SPR
    addInstruction(0xC460, 0xC46F, { IRO | RCI, INC, 0, 0, 0 }); // Increment GPR
    addInstruction(0xC470, 0xC47F, { IRO | RCI, DEC, 0, 0, 0 }); // Decrement GPR
    // addInstruction(0x9000, 0xB888, {  }); // Pop into GPR
    // addInstruction(0x9000, 0xB888, {  }); // Pop into SPR
    // addInstruction(0x9000, 0xB888, {  }); // Push GPR
    // addInstruction(0x9000, 0xB888, {  }); // Push SPR - Can't push SPR 00 (MAR)
    addInstruction(0xC600, 0xC61F, {  }); // Program Counter Immediate Load if flags are set AkA JMP
    addInstruction(0xC620, 0xC63F, {  }); // Program Counter Immediate Load if flags are not set AkA JMP
    addInstruction(0xC620, 0xC63F, {  }); // Program Counter Addressed Load if flags are set AkA JMP
    addInstruction(0xC620, 0xC63F, {  }); // Program Counter Addressed Load if flags are not set AkA JMP


    addInstruction(0xC640, 0xC65F, {  }); // Set flags
    addInstruction(0xC660, 0xC67F, {  }); // Clear flags

    addInstruction(0xC800, 0xC8FF, { IRO | RCI, EO | RI, 0, 0, 0 }); // Bitwise not
    addInstruction(0xD000, 0xFFFF, { IRO | RCI, EO | RI, 0, 0, 0 }); // Bitwise pt 2
    //
    /*
    addInstruction(0x8000, 0x8FFF, { IRO | RCI, SO1 | SRE | RI, EO | BRO | RMI | SI1 | SRE | INC, 0 });
    addInstruction(0x9000, 0x9FFF, { IRO | RCI, SO1 | SRE | RI, RMO | RI, SI1 | SRE | INC });
    */


    // Move register to register
    //
}

