#include "../headers/RAM.h"
#include <cstdint>
#include <exception>
#include <filesystem>
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



uint16_t adr = 0;
void RAM::addValue(uint16_t value)
{
    addValue(adr++, value);
}
void RAM::addValue(uint16_t address, uint16_t value)
{
    adr = address + 1;
    addValue(address, address, value);
}
void RAM::addValue(uint16_t startAddress, uint16_t endAddress, uint16_t value)
{
    adr = endAddress + 1;
    for (; startAddress <= endAddress; startAddress++) {
        values[startAddress] = value;
    }
}

void RAM::setupRAM()
{
    addValue(0xC402); // Load 2 immediate
    addValue(0xA4B2);

    addValue(0xC414); // Load 4 addressed
    addValue(0xD4F8);

    addValue(0x0248); // 2 + 4 > 8

    addValue(0xC448); // Store 8
    addValue(0x0F52);

    addValue(0xC411); // Load 1 addressed
    addValue(0x0F52);

    addValue(0xD4F8, 0x0542);
    // 1 = xA9F4 d43508
    // 2 = xA4B2 d42162
    // 4 = x0542 d01346
    // 8 = xA9F4 d43508
}

