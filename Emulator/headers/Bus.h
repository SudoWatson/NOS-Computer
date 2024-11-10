#pragma once
#include <cstdint>

class Bus {
    uint16_t* ptrValue;
public:
    Bus();
    void Assert(uint16_t* _ptrValue);
    void UnAssert(uint16_t* _ptrValue);
    uint16_t* GetValue();
};
