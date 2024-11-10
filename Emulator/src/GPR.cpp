#include "../headers/GPR.h"

GPR::GPR() {
    value = 0;
}

void GPR::LoadFromMainBus() {
    value = *MainBus->GetValue();
}

void GPR::AssertToLeftHandBus() {
    LeftHandBus->Assert(&value);
}

void GPR::UnAssertToLeftHandBus() {
    LeftHandBus->UnAssert(&value);
}

void GPR::AssertToRightHandBus() {
    RightHandBus->Assert(&value);
}

void GPR::UnAssertToRightHandBus() {
    RightHandBus->UnAssert(&value);
}
