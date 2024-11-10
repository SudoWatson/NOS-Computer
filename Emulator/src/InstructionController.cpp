#include "../headers/InstructionController.h"
#include <cstdint>
#define IC InstructionController

IC::InstructionController(Bus& mainBus) {
    MainBus = &mainBus;
    loadEnable = GetInstructionPtr(IRI);
    for (int i = 0; i < INSTRUCTION_WORD_LENGTH; i++) {
        controlLines[i] = false;
    }

    storedInstruction = 0;
    currentStep = 0;
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

bool* IC::GetInstructionPtr(Instructions ints) {
    return &controlLines[ints];
}

void IC::evaluateStep() {
    uint64_t microinstruction = instructionSet[storedInstruction][currentStep];
    for (int i = 0; i < INSTRUCTION_WORD_LENGTH; i++) {
        controlLines[i] = (microinstruction >> i) & 1;
    }
}

void IC::Clock() {
    if (loadEnable) {
        LoadFromMainBus();
    }

    evaluateStep();
    currentStep++;
    if (currentStep > STEP_SIZE)
        currentStep = 0;
}


/**



evaluateStep(fetch1)

for (int i = 0; i < bitsInInstructionWord; i++) {
    value >> i & 1;
    switch (value) {
        case IRI:
            instructions[IRI] = true
    }
}

[
    [
        fetch 1 = 0b00110010010110010
        fetch 2
        step 3
        step 4
        step 5
        step 6
    ]

]



*/

