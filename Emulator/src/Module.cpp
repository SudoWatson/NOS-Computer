#include "../headers/Module.h"

void Module::performReset() { }
void Module::performClockHigh() { }
void Module::performClockLow() { }
void Module::performUpdateLines() { }
void Module::performConnectControlLines(IInstructionController &ptrIC) { }

void Module::Reset() {
    performReset();
}

void Module::ClockHigh() {
    performClockHigh();
}

void Module::ClockLow() {
    performClockLow();
    UpdateLines();
}

void Module::UpdateLines() {
    performUpdateLines();
}

void Module::ConnectControlLines(IInstructionController &ptrIC) {
    performConnectControlLines(ptrIC);
}
