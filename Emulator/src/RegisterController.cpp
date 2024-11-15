#include "../headers/RegisterController.h"

#define RC RegisterController

RC::RegisterController(Bus& mainBus, Bus& leftHandBus, Bus& rightHandBus) {
    MainBus = &mainBus;
    LeftHandBus = &leftHandBus;
    RightHandBus = &rightHandBus;

    // Initialize the 16 GPRs
    // TODO: Do we actually want to create the 16 registers outside of here and tie them to the RC?
    for (int i = 0; i < GPR_COUNT; i++) {
        *registerEnables[i] = false;
        *registerLHEnables[i] = false;
        *registerRHEnables[i] = false;

        GPR gpr(registerEnables[i], registerLHEnables[i], registerRHEnables[i]);
        gpr.MainBus = MainBus;
        gpr.LeftHandBus = LeftHandBus;
        gpr.RightHandBus = RightHandBus;
        generalRegisters[i] = &gpr;
    }

    performReset();
}

void RC::performReset() {
    value = 0;
    for (auto gpr : generalRegisters) {
        gpr->Reset();
    }
}

void RC::performClockHigh() {
    if (*RegisterControllerIn) {
        LoadFromMainBus();
    }
    for (auto gpr : generalRegisters) {
        gpr->ClockHigh();
    }
}

void RC::performUpdateLines() {
    for (auto gpr : generalRegisters) {
        gpr->UpdateLines();
    }
}

void RC::performConnectControlLines(IInstructionController &ptrIC) {
    RegisterControllerIn = ptrIC.GetControlLinePtr(ptrIC.RCI);
    RegisterIn = ptrIC.GetControlLinePtr(ptrIC.RI);
    for (auto gpr : generalRegisters) {
        gpr->RegisterControlLines(ptrIC, *this);
    }
}

// Methods for getting the various register indexes
// NOTE: Would be nice if these could be like getters
// WARN: Probably needs to be rethinked to get the SPRs working as well
uint8_t RC::registerIndex() {
    return value & 0b1111;
}
uint8_t RC::rhRegisterIndex() {
    return (value >> 4) & 0b1111;
}
uint8_t  RC::lhRegisterIndex() {
    return (value >> 8) & 0b1111;
}

// Interactions between the main bus and the RC internal register
void RC::AssertToMainBus() {
    MainBus->Assert(&value);
}
void RC::UnAssertToMainBus() {
    MainBus->UnAssert(&value);
}
void RC::LoadFromMainBus() {
    *registerEnables[registerIndex()] = false;
    *registerLHEnables[lhRegisterIndex()] = false;
    *registerRHEnables[rhRegisterIndex()] = false;
    value = *MainBus->GetValue();
    *registerEnables[registerIndex()] = true;
    *registerLHEnables[lhRegisterIndex()] = true;
    *registerRHEnables[rhRegisterIndex()] = true;
}

bool* RC::GetRegisterInControlLinePtr() {
    return RegisterIn;
}
