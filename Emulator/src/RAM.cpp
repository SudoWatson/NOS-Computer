#include "../headers/RAM.h"
#include <cstdint>
#include <exception>

RAM::RAM(Bus& mainBus, Bus& marBus) {
    MainBus = &mainBus;
    MARBus = &marBus;
    std::fill(std::begin(values), std::end(values), 0);
}

void RAM::performClockHigh() {
    if (*RAMIn)
    {
        LoadFromMainBus();
    }
}

void RAM::performUpdateLines() {
    if (*RAMOut) {
        AssertToMainBus();
    } else {
        UnAssertToMainBus();
    }
}
void RAM::performConnectControlLines(IInstructionController &ptrIC) {
    RAMOut = ptrIC.GetControlLinePtr(ptrIC.RMO);
    RAMIn = ptrIC.GetControlLinePtr(ptrIC.RMI);
}


void RAM::AssertToMainBus() {
    if (currentlyAsserting != nullptr)  // This might not be necessarry, but it's a sanity check and I'm too tired to fully determine if it's 100% safe without
    {
        MainBus->UnAssert(currentlyAsserting);
    }
    currentlyAsserting = &values[*MARBus->GetValue()];
    MainBus->Assert(currentlyAsserting);
}
void RAM::UnAssertToMainBus() {
    MainBus->UnAssert(&values[*MARBus->GetValue()]);
}

void RAM::LoadFromMainBus() {
    values[*MARBus->GetValue()] = *MainBus->GetValue();
}
