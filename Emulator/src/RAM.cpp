#include "../headers/RAM.h"
#include <cstdint>
#include <exception>
#include <sys/types.h>

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

void RAM::performReset() {
    setupRAM();
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



void RAM::addValue(uint16_t address, uint16_t value)
{
    addValue(address, address, value);
}
void RAM::addValue(uint16_t startAddress, uint16_t endAddress, uint16_t value)
{
    for (; startAddress <= endAddress; startAddress++) {
        values[startAddress] = value;
    }
}

void RAM::setupRAM()
{
    uint16_t adr = 0;
    addValue(adr++, 0x9003);
    addValue(adr++, 0x0002);

    addValue(adr++, 0x9006);
    addValue(adr++, 0x0003);

    addValue(adr++, 0x0360);
}

