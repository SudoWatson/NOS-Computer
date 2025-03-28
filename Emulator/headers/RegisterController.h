#include "Bus.h"
#include "IRegisterController.h"
#include "Module.h"
#include "GPR.h"
#include <cstdint>


class RegisterController : public Module, public IRegisterController {
    // RC Control Lines
    bool* RegisterControllerIn = nullptr;
    bool* RegisterControllerSPREnable = nullptr;
    bool* RegisterControllerSPRIndex1 = nullptr;
    bool* RegisterControllerSPRIndex2 = nullptr;
    bool* RegisterControllerSPROutIndex1 = nullptr;
    bool* RegisterControllerSPROutIndex2 = nullptr;

    // Register Control Lines
    bool* RegisterIn = nullptr;
    bool* Increment = nullptr;
    bool* Decrement = nullptr;

    uint16_t value;
    Bus* MainBus = nullptr;
    Bus* LeftHandBus = nullptr;
    Bus* RightHandBus = nullptr;
    Bus* MARBus = nullptr;

    const static char GPR_COUNT = 0b1111 + 1;
    const static char SPR_COUNT = 0b11 + 1;
    bool* registerEnables[GPR_COUNT];
    bool* registerLHEnables[GPR_COUNT];
    bool* registerRHEnables[GPR_COUNT];

    bool* sprEnables[SPR_COUNT];
    bool* sprOutEnables[SPR_COUNT];

    void performReset() override;
    void performClockHigh() override;
    void performUpdateLines() override;
    void performConnectControlLines(IInstructionController &ptrIC) override;

    uint8_t getGPRIndex();
    uint8_t getGPRRHIndex();
    uint8_t getGPRLHIndex();

    uint8_t getSPRIndex();
    uint8_t getSPROutIndex();

public:
    RegisterController(Bus& mainBus, Bus& leftHandBus, Bus& rightHandBus, Bus& marBus);
    ~RegisterController();

    GPR* generalRegisters[GPR_COUNT];
    GPR* specialRegisters[SPR_COUNT];

    void AssertToMainBus();
    void UnAssertToMainBus();
    void LoadFromMainBus();

    bool* GetRegisterInControlLinePtr() override;
    bool* GetRegisterIncrementLinePtr() override;
    bool* GetRegisterDecrementLinePtr() override;

    uint16_t readValue();
};
