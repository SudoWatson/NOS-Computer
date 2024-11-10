#pragma once
#include "Bus.h"
#include <cstdint>

class GPR {
public:
    uint16_t value;
    Bus* MainBus;
    Bus* LeftHandBus;
    Bus* RightHandBus;

    GPR();

    void LoadFromMainBus();

    void AssertToLeftHandBus();
    void UnAssertToLeftHandBus();

    void AssertToRightHandBus();
    void UnAssertToRightHandBus();
};

