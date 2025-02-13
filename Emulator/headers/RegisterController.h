#include "Bus.h"
#include "IRegisterController.h"
#include "Module.h"
#include "GPR.h"
#include <cstdint>


class RegisterController : public Module, public IRegisterController {
    // RC Control Lines
    bool* RegisterControllerIn = nullptr;

    // Register Control Lines
    bool* RegisterIn = nullptr;

    uint16_t value;
    Bus* MainBus = nullptr;
    Bus* LeftHandBus = nullptr;
    Bus* RightHandBus = nullptr;

    const static char GPR_COUNT = 0b1111 + 1;
    GPR* generalRegisters[GPR_COUNT];
    bool* registerEnables[GPR_COUNT];
    bool* registerLHEnables[GPR_COUNT];
    bool* registerRHEnables[GPR_COUNT];

    void performReset() override;
    void performClockHigh() override;
    void performUpdateLines() override;
    void performConnectControlLines(IInstructionController &ptrIC) override;

    uint8_t registerIndex();
    uint8_t rhRegisterIndex();
    uint8_t lhRegisterIndex();

public:
    RegisterController(Bus& mainBus, Bus& leftHandBus, Bus& rightHandBus);
    ~RegisterController();

    void AssertToMainBus();
    void UnAssertToMainBus();
    void LoadFromMainBus();

    bool* GetRegisterInControlLinePtr() override;
};
