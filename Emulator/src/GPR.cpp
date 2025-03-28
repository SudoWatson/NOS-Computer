#include "../headers/GPR.h"
#include <cstdint>
#include <stdexcept>

GPR::GPR(bool* _ptrEnable, bool* _ptrLHEnable, bool* _ptrRHEnable) {
    ptrEnable = _ptrEnable;
    ptrLHEnable = _ptrLHEnable;
    ptrRHEnable = _ptrRHEnable;
}

void GPR::performReset() {
    value = 0;
}
void GPR::performClockHigh() {
    // If register is enabled and load line on, read
    if (*ptrEnable && *RegisterIn)
    {
        LoadFromMainBus();
    }
    if (*ptrEnable && *Increment)
    {
        value++;
    }
    if (*ptrEnable && *Decrement)
    {
        value--;
    }
}
void GPR::performUpdateLines() {
    // If register is enabled assert
    if (ptrLHEnable != nullptr)
    {
        if (*ptrLHEnable) {
            AssertToLeftHandBus();
        } else {
            UnAssertToLeftHandBus();
        }
    }


    if (*ptrRHEnable) {
        AssertToRightHandBus();
    } else {
        UnAssertToRightHandBus();
    }
}
void GPR::performConnectControlLines(IInstructionController &ptrIC) {
    throw std::invalid_argument("GPRs get some control lines from the Register Controller and as thus need a pointer to the RC");
}

void GPR::performConnectControlLines(IInstructionController &ptrIC, IRegisterController &ptrRC) {
    RegisterIn = ptrRC.GetRegisterInControlLinePtr();
    Increment = ptrRC.GetRegisterIncrementLinePtr();
    Decrement = ptrRC.GetRegisterDecrementLinePtr();
}

void GPR::RegisterControlLines(IInstructionController &ptrIC, IRegisterController &ptrRC)
{
    performConnectControlLines(ptrIC, ptrRC);
}

void GPR::LoadFromMainBus() {
    value = *(MainBus->GetValue());
}

void GPR::AssertToLeftHandBus() {
    LeftHandBus->Assert(&value);
}

void GPR::UnAssertToLeftHandBus() {
    LeftHandBus->UnAssert(&value);
}

void GPR::AssertToRightHandBus() {
    RightHandBus->Assert(&value);
}

void GPR::UnAssertToRightHandBus() {
    RightHandBus->UnAssert(&value);
}

uint16_t GPR::readValue()
{
    return value;
}
