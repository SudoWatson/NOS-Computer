#include "../headers/GPR.h"

GPR::GPR() {
    value = 0;
}

void GPR::AssertToMainBus() {
    MainBus->AssertFrom(this);
}

void GPR::UnAssertToMainBus() {
    MainBus->UnAssertFrom(this);
}

void GPR::LoadFromMainBus() {
    value = MainBus->ReadValue();
}
