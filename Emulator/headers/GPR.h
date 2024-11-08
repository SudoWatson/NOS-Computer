#pragma once
#include "Bus.h"
#include "IHasValue.h"

class GPR : public IHasValue {
public:
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

