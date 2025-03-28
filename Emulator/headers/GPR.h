#pragma once

#include "Bus.h"
#include "Module.h"
#include "IRegisterController.h"
#include <cstdint>

class GPR : public Module {
    uint16_t value;

    bool* ptrEnable = nullptr;
    bool* ptrLHEnable = nullptr;
    bool* ptrRHEnable = nullptr;

    bool* RegisterIn = nullptr;
    bool* Increment = nullptr;
    bool* Decrement = nullptr;

    void performReset() override;
    void performClockHigh() override;
    void performUpdateLines() override;
    void performConnectControlLines(IInstructionController &ptrIC) override;
    void performConnectControlLines(IInstructionController &ptrIC, IRegisterController &ptrRC);

public:
    GPR(bool* _ptrEnable, bool* _ptrLHEnable, bool* _ptrRHEnable);
    Bus* MainBus = nullptr;
    Bus* LeftHandBus = nullptr;
    Bus* RightHandBus = nullptr;

    void LoadFromMainBus();

    void AssertToLeftHandBus();
    void UnAssertToLeftHandBus();

    void AssertToRightHandBus();
    void UnAssertToRightHandBus();

    void RegisterControlLines(IInstructionController &ptrIC, IRegisterController &ptrRC);

    uint16_t readValue();
};

