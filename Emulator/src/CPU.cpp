#include "../headers/CPU.h"
#include "InstructionController.h"


void CPU::performReset() {
    rc->Reset();
    ic->Reset();
    alu->Reset();
    ram->Reset();
}
void CPU::performClockHigh() {
    rc->ClockHigh();
    ic->ClockHigh();
    alu->ClockHigh();
    ram->ClockHigh();
}
void CPU::performClockLow() {
    rc->ClockLow();
    ic->ClockLow();
    alu->ClockLow();
    ram->ClockLow();
}
void CPU::performUpdateLines() {
    rc->UpdateLines();
    ic->UpdateLines();
    alu->UpdateLines();
    ram->UpdateLines();
}
void CPU::performConnectControlLines(IInstructionController &ptrIC) {
    rc->ConnectControlLines(ptrIC);
    ic->ConnectControlLines(ptrIC);
    alu->ConnectControlLines(ptrIC);
    ram->ConnectControlLines(ptrIC);
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

    ic = new InstructionController(*MainBus);

    alu = new ALU(*MainBus, *LhBus, *RhBus);

    ram = new RAM(*MainBus, marBus);

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
