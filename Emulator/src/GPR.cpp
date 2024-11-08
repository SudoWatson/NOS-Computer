#include "../headers/GPR.h"

GPR::GPR() {
    value = 0;
}

void GPR::LoadFromMainBus() {
    value = *MainBus->GetValue();
}

void GPR::AssertToLeftHandBus() {
    LeftHandBus->AssertFrom(&value);
}

void GPR::UnAssertToLeftHandBus() {
    LeftHandBus->UnAssertFrom(&value);
}

void GPR::AssertToRightHandBus() {
    RightHandBus->AssertFrom(&value);
}

void GPR::UnAssertToRightHandBus() {
    RightHandBus->UnAssertFrom(&value);
}
