#include "Bus.h"
#include "Module.h"
#include <cstdint>

class ALU : Module {
    bool* BypassRegisterOut = nullptr;

    uint16_t value;
    Bus* MainBus;
    Bus* LeftHandBus;
    Bus* RightHandBus;

    void calculateValue();

    virtual void performClockHigh() override;
    virtual void performUpdateLines() override;
    virtual void performRegisterControlLines(IInstructionController &ptrIC) override;

public:
    ALU(Bus& mainBus, Bus& leftHandBus, Bus& rightHandBus);

    void AssertToMainBus();
    void UnAssertToMainBus();
};
