#include "Bus.h"
#include <iostream>

Bus::Bus() {
    valueHoldingObject = nullptr;
}

void Bus::AssertTo(IHasValue* valueHolder) {
    if (valueHoldingObject != nullptr) {
        std::cout << "Trying to assert to the bus when already asserted to via " << valueHoldingObject;
    }

    valueHoldingObject = valueHolder;
}

void Bus::UnAssertSelf(IHasValue* valueHolder) {
    if (valueHoldingObject == valueHolder) {
        valueHoldingObject = nullptr;
    }
}

uint16_t Bus::ReadFrom() {
    if (valueHoldingObject == nullptr) return 0;
    return valueHoldingObject->value;
}
