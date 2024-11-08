#include "../headers/GPR.h"

GPR::GPR() {
    value = 0;
}

void GPR::LoadFromMainBus() {
    value = MainBus->ReadValue();
}

void GPR::AssertToLeftHandBus() {
    LeftHandBus->AssertFrom(this);
}

void GPR::UnAssertToLeftHandBus() {
    LeftHandBus->UnAssertFrom(this);
}

void GPR::AssertToRightHandBus() {
    RightHandBus->AssertFrom(this);
}

void GPR::UnAssertToRightHandBus() {
    RightHandBus->UnAssertFrom(this);
}
