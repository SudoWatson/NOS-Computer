#pragma once
#include "IHasValue.h"

class Bus {
    IHasValue* valueHoldingObject;
public:
    Bus();
    void AssertTo(IHasValue* valueHolder);
    void UnAssertSelf(IHasValue* valueHolder);
    uint16_t ReadFrom();
};
