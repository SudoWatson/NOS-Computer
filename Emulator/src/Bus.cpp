#include "../headers/Bus.h"
#include <cstdint>
#include <iostream>

Bus::Bus() {
    ptrValue = nullptr;
}

void Bus::AssertFrom(IHasValue* valueHolder) {
    if (ptrValue != nullptr) {
        std::cout << "Trying to assert to the bus when already asserted to via " << ptrValue;
    }

    ptrValue = &(valueHolder->value);
}

void Bus::UnAssertFrom(IHasValue* valueHolder) {
    if (ptrValue == &(valueHolder->value)) {
        ptrValue = nullptr;
    }
}

void Bus::AssertFrom(uint16_t* _ptrValue) {
    if (ptrValue != nullptr) {
        std::cout << "Trying to assert to the bus when already asserted to via " << ptrValue;
    }

    ptrValue = _ptrValue;
}

void Bus::UnAssertFrom(uint16_t* _ptrValue) {
    if (ptrValue == _ptrValue) {
        ptrValue = nullptr;
    }
}

uint16_t* Bus::GetValue() {
    if (ptrValue == nullptr) return 0;
    return ptrValue;
}
