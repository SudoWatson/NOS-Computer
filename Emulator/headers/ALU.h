#include "Bus.h"
#include "Module.h"
#include <cstdint>

class ALU : public Module {
    bool* BypassRegisterOut = nullptr;
    bool* ALUResultOut = nullptr;
    bool* ALUInstructionIn = nullptr;

    uint16_t value;
    uint8_t instructionValue;
    Bus* MainBus = nullptr;
    Bus* LeftHandBus = nullptr;
    Bus* RightHandBus = nullptr;

    void calculateValue();
    void calculateArithmeticValue();
    void calculateLogicValue();

    void calculateShiftLogic();
    void calculateBitwiseLogic();


    virtual void performClockHigh() override;
    virtual void performUpdateLines() override;
    virtual void performConnectControlLines(IInstructionController &ptrIC) override;

public:
    ALU(Bus& mainBus, Bus& leftHandBus, Bus& rightHandBus);

    void AssertToMainBus();
    void UnAssertToMainBus();
    void LoadFromMainBus();
};
