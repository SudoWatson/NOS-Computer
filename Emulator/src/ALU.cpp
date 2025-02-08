#include "../headers/ALU.h"
#include <cstdint>
#include <exception>

ALU::ALU(Bus& mainBus, Bus& leftHandBus, Bus& rightHandBus) {
    value = 0;
    instructionValue = 0;
    MainBus = &mainBus;
    LeftHandBus = &leftHandBus;
    RightHandBus = &rightHandBus;
}

void ALU::performClockHigh() {
    if (*ALUInstructionIn)
    {
        LoadFromMainBus();
    }
}

void ALU::performUpdateLines() {
    if (*BypassRegisterOut || *ALUResultOut) {
        AssertToMainBus();
    } else {
        UnAssertToMainBus();
    }
}
void ALU::performConnectControlLines(IInstructionController &ptrIC) {
    BypassRegisterOut = ptrIC.GetControlLinePtr(ptrIC.BRO);
    ALUResultOut = ptrIC.GetControlLinePtr(ptrIC.EO);
    ALUInstructionIn = ptrIC.GetControlLinePtr(ptrIC.EI);
}

// NOTE: We only calculate the new value when the ALU asserts.
// I don't know how to have it just update it's value if the LH/RH bus pointers change without writing way more than is worth it rn
// Also don't know how to have it update when the value of a register changes
// Maybe, if we have a method that reads from the bus, we can have that call an abstract method on Module (something like busUpdated) that, in the ALU case, will rerun the calculateValue method?
void ALU::calculateValue() {
    // BRO
    if (*BypassRegisterOut) {
        value = *RightHandBus->GetValue();
        return;
    }

    if (((instructionValue >> 4) & 0b1000) != 0b1000)
    {  // First bit 0
        calculateArithmeticValue();
    }
    else
    {  // First bit 1
        calculateLogicValue();
    }
}

void ALU::calculateArithmeticValue() {
    // Bit 2 unused
    // Bit 3 Operation
    // Bit 4 Use Carry Flag
    // TODO: Handle carry in flag
    if (((instructionValue >> 4) & 0b0010) != 0b0010)
    {  // Third bit 0
        value = *LeftHandBus->GetValue() + *RightHandBus->GetValue() ;
        return;
    }
    else
    {  // Third bit 1
        value = *LeftHandBus->GetValue() - *RightHandBus->GetValue() ;
        return;
    }
}

void ALU::calculateLogicValue() {
    if (((instructionValue >> 4) & 0b0011) == 0b0000)
    {  // Last 2 bits both 0
        // Instruction is 1X00-XXXX
        if (((instructionValue >> 4) & 0b00001) != 0b00001)
        {  // Fifth bit 0
            calculateShiftLogic();
        }
        else
        {  // Fifth bit 1
            calculateBitwiseLogic();
        }
    }
    else
    {  // Last 2 bits not both 0
        calculateBitwiseLogic();
    }
}

void ALU::calculateShiftLogic() {
    // Instructin is 1X00-1XXX
    if ((instructionValue & 0b0100) != 0b0100)
    {  // Second bit 0 in second nibble
        // Rotate
        // TODO: Handle carry and fourth bit of second nibble
        if ((instructionValue & 0b0010) != 0b0100)
        {  // Third bit 0 in second nibble
            bool fallingValue = value & (0b1 << 15) >> 15;
            value = (*RightHandBus->GetValue() << 1) + fallingValue;
        }
        else
        {  // Third bit 1 in second nibble
            bool fallingValue = value & 0b1;
            value = (*RightHandBus->GetValue() >> 1) + (fallingValue << 15);
        }
    }
    else
    {  // Second bit 1 in second nibble
        // Shift
        // TODO: Handle carry and fourth bit of second nibble
        if ((instructionValue & 0b0010) != 0b0100)
        {  // Third bit 0 in second nibble
            value = *RightHandBus->GetValue() << 1; 
        }
        else
        {  // Third bit 1 in second nibble
            value = *RightHandBus->GetValue() >> 1; 
        }
    }
}

void ALU::calculateBitwiseLogic() {
    uint16_t preValue;
    switch ((instructionValue >> 4) & 0b0011)
    {
        case 0b00:
            preValue = *RightHandBus->GetValue();
            break;
        case 0b01:
            preValue = *LeftHandBus->GetValue() & *RightHandBus->GetValue();
            break;
        case 0b10:
            preValue = *LeftHandBus->GetValue() | *RightHandBus->GetValue();
            break;
        case 0b11:  // XOR
            preValue = *LeftHandBus->GetValue() ^ *RightHandBus->GetValue();
            break;
        default:
            throw new std::exception();  // I don't even know how this could happen
    }
    if ((instructionValue & 0b0100) == 0b0100)
    {
        preValue = ~preValue;  // Not
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
    instructionValue = *MainBus->GetValue() >> 8;  // Left 8 bits taken
}
