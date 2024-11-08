#pragma once
#include "Bus.h"
#include "IHasValue.h"
#include <cstdint>

class GPR : IHasValue {
public:
    uint16_t* leftHandBus;
    uint16_t* rightHandBus;
    Bus* mainBus;

    void increment();
    void decrament();
    void assert();
    void load();

    uint16_t getValue();
    void setValue(uint16_t val);
};
