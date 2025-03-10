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
uint16_t RAM::addValue(uint16_t value)
{
    return addValue(adr, value);
}
uint16_t RAM::addValue(uint16_t address, uint16_t value)
{
    return addValue(address, address, value);
}
uint16_t RAM::addValue(uint16_t startAddress, uint16_t endAddress, uint16_t value)
{
    for (; startAddress <= endAddress; startAddress++) {
        values[startAddress] = value;
    }
    adr = endAddress + 1;
    return endAddress;
}

void RAM::setupRAM()
{
    // --== Fibonnaci Sequence ==-- \\
    // Load 0 with 0
    // Load 1 with 1
    // Start Loop
    // 0 + 1 > 0
    // 0 + 1 > 1
    // jmp to loop start


    // Load r0 with 0
    addValue(0xC400);
    addValue(0x0000);
    // Load r1 with 1
    addValue(0xC401);
    addValue(0x0001);

    // 0 + 1 > 0
    uint16_t startLoopAdr = addValue(0x0010);
    // 0 + 1 > 1
    addValue(0x0011);
    // JMP to loop start
    addValue(0x4C00);  // JMP immediate with 0 mask testing 0 flag
    addValue(startLoopAdr);  // JMP location
}

