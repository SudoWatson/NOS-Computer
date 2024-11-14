#include "GPR.h"
#include "Bus.h"
#include "Module.h"
#include <cstdint>

class RegisterController : Module {
    bool* RegisterControllerIn = nullptr;
    bool* RegisterIn = nullptr;

    uint16_t value;
    Bus* MainBus;
    Bus* LeftHandBus;
    Bus* RightHandBus;
    GPR generalRegisters[16];

    uint8_t registerIndex();
    uint8_t rhRegisterIndex();
    uint8_t lhRegisterIndex();

    void unAssertRegisters();
    void assertRegisters();

public:
    RegisterController(Bus& mainBus, Bus& leftHandBus, Bus& rightHandBus);

    void performReset() override;
    void performClockHigh() override;
    void performUpdateLines() override;
    void performRegisterControlLines(IInstructionController &ptrIC) override;

    void LoadFromMainBusToRegister();

    void AssertToMainBus();
    void UnAssertToMainBus();
    void LoadFromMainBus();
};
