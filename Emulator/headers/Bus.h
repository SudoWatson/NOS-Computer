#pragma once
#include <cstdint>

class Bus {
public:
    uint16_t* ptrValue = nullptr;
public:
    Bus();
    void Assert(uint16_t* _ptrValue);
    void UnAssert(uint16_t* _ptrValue);
    uint16_t* GetValue();
};
