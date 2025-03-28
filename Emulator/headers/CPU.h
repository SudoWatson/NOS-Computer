#pragma once

#include "InstructionController.h"
#include "Module.h"
#include "ALU.h"
#include "RAM.h"
#include "RegisterController.h"
#include <vector>

/** Sends common controls such as reset and clocking to all modules */
class CPU : public Module {
    std::vector<Module*> modulePtrs;
    virtual void performReset() override;
    virtual void performClockHigh() override;
    virtual void performClockLow() override;
    virtual void performUpdateLines() override;
    virtual void performConnectControlLines(IInstructionController &ptrIC) override;

    RegisterController* rc = nullptr;
    InstructionController* ic = nullptr;
    RAM* ram = nullptr;
    ALU* alu = nullptr;

    Bus* MainBus = nullptr;
    Bus* LhBus = nullptr;
    Bus* RhBus = nullptr;

public:
    CPU();
    ~CPU();

    void AddModule(Module* ptrModule);
    void FullCycle();
};

