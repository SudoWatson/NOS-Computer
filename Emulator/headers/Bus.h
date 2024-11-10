#pragma once
#include <cstdint>

class Bus {
    uint16_t* ptrValue;
public:
    Bus();
    void AssertFrom(uint16_t* _ptrValue);
    void UnAssertFrom(uint16_t* _ptrValue);
    uint16_t* GetValue();
};
