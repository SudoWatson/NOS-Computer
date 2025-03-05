#include "../headers/RegisterController.h"
#include "iostream"

#define RC RegisterController

RC::RegisterController(Bus& mainBus, Bus& leftHandBus, Bus& rightHandBus) {
    MainBus = &mainBus;
    LeftHandBus = &leftHandBus;
    RightHandBus = &rightHandBus;

    // Initialize the 16 GPRs
    // TODO: Do we actually want to create the 16 registers outside of here and tie them to the RC?
    for (int i = 0; i < GPR_COUNT; i++) {
        bool* enable =  new bool(false);
        bool* lhEnable = new bool(false);
        bool* rhEnable = new bool(false);

        registerEnables[i] = enable;
        registerLHEnables[i] = lhEnable;
        registerRHEnables[i] = rhEnable;

        GPR* gpr = new GPR(registerEnables[i], registerLHEnables[i], registerRHEnables[i]);
        gpr->MainBus = MainBus;
        gpr->LeftHandBus = LeftHandBus;
        gpr->RightHandBus = RightHandBus;
        generalRegisters[i] = gpr;
    }

    for (int i = 0; i < SPR_COUNT; i++) {
        bool* enable =  new bool(false);
        bool* outEnable =  new bool(false);

        sprEnables[i] = enable;
        sprOutEnables[i] = outEnable;

        GPR* spr = new GPR(sprEnables[i], nullptr, sprOutEnables[i]);
        spr->MainBus = MainBus;
        spr->RightHandBus = RightHandBus;  // TODO: Can this just be the main bus?
        specialRegisters[i] = spr;
    }
}

RC::~RegisterController() {
    for (int i = 0; i < GPR_COUNT; i++) {
        delete generalRegisters[i];
        delete registerEnables[i];
        delete registerLHEnables[i];
        delete registerRHEnables[i];
    }

    for (int i = 0; i < SPR_COUNT; i++) {
        delete specialRegisters[i];
        delete sprEnables[i];
        delete sprOutEnables[i];
    }
}

void RC::performReset() {
    value = 0;
    for (GPR* gpr : generalRegisters) {
        gpr->Reset();
    }
    for (GPR* spr : specialRegisters) {
        spr->Reset();
    }
}

void RC::performClockHigh() {
    if (*RegisterControllerIn) {
        LoadFromMainBus();
    }
    for (GPR* gpr : generalRegisters) {
        gpr->ClockHigh();
    }
    for (GPR* spr : specialRegisters) {
        spr->ClockHigh();
    }
}

void RC::performUpdateLines() {
    for (GPR* gpr : generalRegisters) {
        gpr->UpdateLines();
    }
    for (GPR* spr : specialRegisters) {
        spr->UpdateLines();
    }


    for (int i = 0; i < SPR_COUNT; i++) {
        *sprEnables[i] = false;
        *sprOutEnables[i] = false;
    }
    if (*RegisterControllerSPREnable) {
        *sprEnables[getSPRIndex()] = true;
    }
    if (*RegisterControllerSPROutIndex1 || *RegisterControllerSPROutIndex2) {
        *sprOutEnables[getSPROutIndex()] = true;
    }
}

uint8_t RC::getSPRIndex() {
    return (*RegisterControllerSPRIndex2 << 1) | *RegisterControllerSPRIndex1;
}

uint8_t RC::getSPROutIndex() {
    return (*RegisterControllerSPROutIndex2 << 1) | *RegisterControllerSPROutIndex1;
}

void RC::performConnectControlLines(IInstructionController &ptrIC) {
    RegisterControllerIn = ptrIC.GetControlLinePtr(ptrIC.RCI);
    RegisterIn = ptrIC.GetControlLinePtr(ptrIC.RI);

    RegisterControllerSPREnable = ptrIC.GetControlLinePtr(ptrIC.SRE);

    RegisterControllerSPRIndex1 = ptrIC.GetControlLinePtr(ptrIC.SI1);
    RegisterControllerSPRIndex2 = ptrIC.GetControlLinePtr(ptrIC.SI2);

    RegisterControllerSPROutIndex1 = ptrIC.GetControlLinePtr(ptrIC.SO1);
    RegisterControllerSPROutIndex2 = ptrIC.GetControlLinePtr(ptrIC.SO2);

    for (GPR* gpr : generalRegisters) {
        gpr->RegisterControlLines(ptrIC, *this);
    }
    for (GPR* spr : specialRegisters) {
        spr->RegisterControlLines(ptrIC, *this);
    }
}

// Methods for getting the various register indexes
// NOTE: Would be nice if these could be like getters
// WARN: Probably needs to be rethinked to get the SPRs working as well
uint8_t RC::getGPRIndex() {
    return value & 0b1111;
}
uint8_t RC::getGPRRHIndex() {
    return (value >> 4) & 0b1111;
}
uint8_t  RC::getGPRLHIndex() {
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
    *registerEnables[getGPRIndex()] = false;
    *registerRHEnables[getGPRRHIndex()] = false;
    *registerLHEnables[getGPRLHIndex()] = false;
    value = *MainBus->GetValue();
    *registerLHEnables[getGPRLHIndex()] = true;

    if (!*RegisterControllerSPREnable) {
        *registerEnables[getGPRIndex()] = true;
    }

    if (!*RegisterControllerSPROutIndex1 && !*RegisterControllerSPROutIndex2) {
        *registerRHEnables[getGPRRHIndex()] = true;
    }

}

bool* RC::GetRegisterInControlLinePtr() {
    return RegisterIn;
}
