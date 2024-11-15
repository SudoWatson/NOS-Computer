#include "../headers/ModuleCommonControl.h"


void ModuleCommonControl::performReset() {
    for (auto module : modulePtrs) {
        module->Reset();
    }
}
void ModuleCommonControl::performClockHigh() {
    for (auto module : modulePtrs) {
        module->ClockHigh();
    }
}
void ModuleCommonControl::performClockLow() {
    for (auto module : modulePtrs) {
        module->ClockLow();
    }
}
void ModuleCommonControl::performUpdateLines() {
    for (auto module : modulePtrs) {
        module->UpdateLines();
    }
}
void ModuleCommonControl::performConnectControlLines(IInstructionController &ptrIC) {
    for (auto module : modulePtrs) {
        module->ConnectControlLines(ptrIC);
    }
}

void ModuleCommonControl::AddModule(Module* ptrModule) {
    modulePtrs.push_back(ptrModule);
}
