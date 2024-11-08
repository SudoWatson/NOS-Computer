#include "../headers/Bus.h"
#include <iostream>

Bus::Bus() {
    valueHoldingObject = nullptr;
}

void Bus::AssertFrom(IHasValue* valueHolder) {
    if (valueHoldingObject != nullptr) {
        std::cout << "Trying to assert to the bus when already asserted to via " << valueHoldingObject;
    }

    valueHoldingObject = valueHolder;
}

void Bus::UnAssertFrom(IHasValue* valueHolder) {
    if (valueHoldingObject == valueHolder) {
        valueHoldingObject = nullptr;
    }
}

uint16_t Bus::ReadValue() {
    if (valueHoldingObject == nullptr) return 0;
    return valueHoldingObject->value;
}
