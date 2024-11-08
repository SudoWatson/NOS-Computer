#include "Bus.h"
#include "IHasValue.h"

class ALU : IHasValue {
    Bus* MainBus;
    Bus* LeftHandBus;
    Bus* RightHandBus;

    void calculateValue();

public:
    ALU(Bus& mainBus, Bus& leftHandBus, Bus& rightHandBus);

    void AssertToMainBus();
    void UnAssertToMainBus();
};
