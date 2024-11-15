#include "Bus.h"
#include "Module.h"
#include <cstdint>

class ALU : public Module {
    bool* BypassRegisterOut = nullptr;

    uint16_t value;
    Bus* MainBus = nullptr;
    Bus* LeftHandBus = nullptr;
    Bus* RightHandBus = nullptr;

    void calculateValue();

    virtual void performClockHigh() override;
    virtual void performUpdateLines() override;
    virtual void performConnectControlLines(IInstructionController &ptrIC) override;

public:
    ALU(Bus& mainBus, Bus& leftHandBus, Bus& rightHandBus);

    void AssertToMainBus();
    void UnAssertToMainBus();
};
