#pragma once
#include "Bus.h"
#include "IHasValue.h"
#include <cstdint>

class GPR : IHasValue {
public:
    GPR();
    uint16_t* leftHandBus;
    uint16_t* rightHandBus;
    Bus* MainBus;

    void AssertToMainBus();
    void UnAssertToMainBus();
    void LoadFromMainBus();
};
