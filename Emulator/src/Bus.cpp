#include "../headers/Bus.h"
#include <cstdint>
// #include <iostream>

Bus::Bus() {
    ptrValue = nullptr;
}

void Bus::Assert(uint16_t* _ptrValue) {
    // NOTE: Commenting this should allow me to change devices that are asserting without breaking
    // if (ptrValue != nullptr) {
    //     std::cout << "Trying to assert to the bus when already asserted to via " << ptrValue;
    // }

    ptrValue = _ptrValue;
}

void Bus::UnAssert(uint16_t* _ptrValue) {
    if (ptrValue == _ptrValue) {
        ptrValue = nullptr;
    }
}

uint16_t* Bus::GetValue() {
    if (ptrValue == nullptr) return 0;
    return ptrValue;
}
