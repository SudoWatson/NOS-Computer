#include "../headers/ALU.h"

ALU::ALU(Bus& mainBus, Bus& leftHandBus, Bus& rightHandBus) {
    value = 0;
    instructionValue = 0;
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
// Also don't know how to have it update when the value of a register changes
void ALU::calculateValue() {
    // BRO
    if (*BypassRegisterOut) {
        value = *RightHandBus->GetValue();
        return;
    }

    if ((instructionValue & 0b1000) != 0b1000)
    {  // Arithmetic

        // TODO: Handle carry in flag
        if ((instructionValue & 0b0010) != 0b0010)
        {
            value = *RightHandBus->GetValue() - *LeftHandBus->GetValue();
            return;
        }
        else
        {
            value = *RightHandBus->GetValue() + *LeftHandBus->GetValue();
            return;
        }
    }
    else
    {  // Logic

        // Check for Shift/Rotate
        // Check for Register
        // Otherwise it's a bitwise operation
    }
}

// Interactions between the main bus and ALU
void ALU::AssertToMainBus() {
    calculateValue();
    MainBus->Assert(&value);
}
void ALU::UnAssertToMainBus() {
    MainBus->UnAssert(&value);
}

void ALU::LoadFromMainBus() {
    instructionValue = *MainBus->GetValue();
}
