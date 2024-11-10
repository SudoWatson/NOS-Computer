#include "Bus.h"
#include <cstdint>

class ALU {
    uint16_t value;
    Bus* MainBus;
    Bus* LeftHandBus;
    Bus* RightHandBus;

    void calculateValue();

public:
    ALU(Bus& mainBus, Bus& leftHandBus, Bus& rightHandBus);

    void AssertToMainBus();
    void UnAssertToMainBus();
};
