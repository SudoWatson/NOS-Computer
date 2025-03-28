#include "../headers/CPU.h"
#include "InstructionController.h"


void CPU::performReset() {
    for (auto module : modulePtrs) {
        module->Reset();
    }
}
void CPU::performClockHigh() {
    for (auto module : modulePtrs) {
        module->ClockHigh();
    }
}
void CPU::performClockLow() {
    for (auto module : modulePtrs) {
        module->ClockLow();
    }
}
void CPU::performUpdateLines() {
    for (auto module : modulePtrs) {
        module->UpdateLines();
    }
}
void CPU::performConnectControlLines(IInstructionController &ptrIC) {
    for (auto module : modulePtrs) {
        module->ConnectControlLines(ptrIC);
    }
}

void CPU::AddModule(Module* ptrModule) {
    modulePtrs.push_back(ptrModule);
}

void CPU::FullCycle() {
    ClockHigh();
    ClockLow();
}


CPU::CPU()
{
    MainBus = new Bus();
    LhBus = new Bus();
    RhBus = new Bus();
    Bus marBus;

    rc = new RegisterController(*MainBus, *LhBus, *RhBus, marBus);
    AddModule(rc);

    ic = new InstructionController(*MainBus);
    AddModule(ic);

    alu = new ALU(*MainBus, *LhBus, *RhBus);
    AddModule(alu);

    ram = new RAM(*MainBus, marBus);
    AddModule(ram);

    ConnectControlLines(*ic);

    Reset();
    UpdateLines();
}

CPU::~CPU()
{
    delete MainBus;
    delete LhBus;
    delete RhBus;

    delete rc;
    delete ic;
    delete alu;
    delete ram;
}
