#include "../headers/ALU.h"

ALU::ALU(Bus& mainBus, Bus& leftHandBus, Bus& rightHandBus) {
    value = 0;
    MainBus = &mainBus;
    LeftHandBus = &leftHandBus;
    RightHandBus = &rightHandBus;
}

void ALU::performClockHigh() {
}
void ALU::performUpdateLines() {
    if (*BypassRegisterOut) {
        AssertToMainBus();
    }
}
void ALU::performConnectControlLines(IInstructionController &ptrIC) {
    BypassRegisterOut = ptrIC.GetControlLinePtr(ptrIC.BRO);
}

// NOTE: We only calculate the new value when the ALU asserts.
// I don't know how to have it just update it's value if the LH/RH bus pointers change without writing way more than is worth it rn
void ALU::calculateValue() {
    // BRO
    if (*BypassRegisterOut) {
        value = *RightHandBus->GetValue();
        return;
    }

    value = *RightHandBus->GetValue() + *LeftHandBus->GetValue();
}

// Interactions between the main bus and ALU
void ALU::AssertToMainBus() {
    calculateValue();
    MainBus->Assert(&value);
}
void ALU::UnAssertToMainBus() {
    MainBus->UnAssert(&value);
}

