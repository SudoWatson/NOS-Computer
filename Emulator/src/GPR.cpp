#include "GPR.h"

void GPR::increment() {
    value++;
}

void GPR::decrament() {
    value--;
}

void GPR::assert() {
    mainBus->AssertTo(this);
}

void GPR::load() {
    value = mainBus->ReadFrom();
}

uint16_t GPR::getValue() {
    return value;
}

void GPR::setValue(uint16_t val) {
    value = val;
}
