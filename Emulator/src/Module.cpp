#include "../headers/Module.h"

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
    RegisterControlLines(ptrIC);
}
