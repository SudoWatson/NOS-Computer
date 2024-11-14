#pragma once

#include "Module.h"
#include <vector>

/** Sends common controls such as reset and clocking to all modules */
class ModuleCommonControl : public Module {
    std::vector<Module*> modulePtrs;
    virtual void performReset() override;
    virtual void performClockHigh() override;
    virtual void performClockLow() override;
    virtual void performUpdateLines() override;
    virtual void performRegisterControlLines(IInstructionController &ptrIC) override;

public:
    void AddModule(Module* ptrModule);
};

