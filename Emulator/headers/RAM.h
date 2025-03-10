#include "Bus.h"
#include "Module.h"
#include <cstdint>

class RAM : public Module {
    bool* RAMOut = nullptr;
    bool* RAMIn = nullptr;

    uint16_t* currentlyAsserting = nullptr;

    Bus* MainBus = nullptr;
    Bus* MARBus = nullptr;

    virtual void performClockHigh() override;
    virtual void performUpdateLines() override;
    virtual void performConnectControlLines(IInstructionController &ptrIC) override;
    virtual void performReset() override;

    uint16_t addValue(uint16_t value);
    uint16_t addValue(uint16_t startAddress, uint16_t value);
    uint16_t addValue(uint16_t startAddress, uint16_t endAddress, uint16_t value);
    void setupRAM();

public:
    uint16_t values[0xFFFF+1] = {0};
    RAM(Bus& mainBus, Bus& MARBus);

    void AssertToMainBus();
    void UnAssertToMainBus();
    void LoadFromMainBus();
};
