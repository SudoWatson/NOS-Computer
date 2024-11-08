#include "../headers/RegisterController.h"

#define RC RegisterController

RC::RegisterController(Bus& mainBus, Bus& leftHandBus, Bus& rightHandBus) {
    value = 0;
    MainBus = &mainBus;
    LeftHandBus = &leftHandBus;
    RightHandBus = &rightHandBus;

    // Initialize the 16 GPRs
    // TODO: Do we actually want to create the 16 registers outside of here and tie them to the RC?
    for (int i = 0; i < sizeof(generalRegisters)/sizeof(*generalRegisters); i++) {
        GPR gpr;
        gpr.MainBus = MainBus;
        gpr.LeftHandBus = LeftHandBus;
        gpr.RightHandBus = RightHandBus;
        generalRegisters[i] = gpr;
    }
    assertRegisters();
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

// Interactions between the busses and selected registers
void RC::unAssertRegisters() {
    generalRegisters[lhRegisterIndex()].UnAssertToLeftHandBus();
    generalRegisters[rhRegisterIndex()].UnAssertToRightHandBus();
}

void RC::assertRegisters() {
    generalRegisters[lhRegisterIndex()].AssertToLeftHandBus();
    generalRegisters[rhRegisterIndex()].AssertToRightHandBus();
}

void RC::LoadFromMainBusToRegister() {
    generalRegisters[registerIndex()].LoadFromMainBus();
}

// Interactions between the main bus and the RC internal register
void RC::AssertToMainBus() {
    MainBus->AssertFrom(this);
}
void RC::UnAssertToMainBus() {
    MainBus->UnAssertFrom(this);
}
void RC::LoadFromMainBus() {
    // GPRs that are asserting on the bus is determined by the internal register, so we want to change the ones asserting when the RC updates
    unAssertRegisters();
    value = MainBus->ReadValue();
    assertRegisters();
}

