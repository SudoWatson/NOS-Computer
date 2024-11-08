#include "GPR.h"
#include "Bus.h"
#include "IHasValue.h"
#include <cstdint>

class RegisterController : public IHasValue {
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

    void LoadFromMainBusToRegister();

    void AssertToMainBus();
    void UnAssertToMainBus();
    void LoadFromMainBus();
};
