#include "../headers/Module.h"

void Module::performReset() { }
void Module::performClockHigh() { }
void Module::performClockLow() { }
void Module::performUpdateLines() { }
void Module::performRegisterControlLines(IInstructionController &ptrIC) { }

void Module::Reset() {
    performReset();
    performUpdateLines();
}

void Module::ClockHigh() {
    performClockHigh();
}

void Module::ClockLow() {
    performClockLow();
}

void Module::UpdateLines() {
    performUpdateLines();
}

void Module::RegisterControlLines(IInstructionController &ptrIC) {
    performRegisterControlLines(ptrIC);
}
