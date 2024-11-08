#pragma once
#include "IHasValue.h"
#include <cstdint>

class Bus {
    uint16_t* ptrValue;
public:
    Bus();
    void AssertFrom(IHasValue* valueHolder);
    void UnAssertFrom(IHasValue* valueHolder);
    void AssertFrom(uint16_t* _ptrValue);
    void UnAssertFrom(uint16_t* _ptrValue);
    uint16_t* GetValue();
};
