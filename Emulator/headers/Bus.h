#pragma once
#include "IHasValue.h"

class Bus {
    IHasValue* valueHoldingObject;
public:
    Bus();
    void AssertFrom(IHasValue* valueHolder);
    void UnAssertFrom(IHasValue* valueHolder);
    uint16_t ReadValue();
};
