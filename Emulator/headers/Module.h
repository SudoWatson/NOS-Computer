#pragma once
#include "IInstructionController.h"
class Module {
private:
    virtual void performReset();

    /** Triggers the clock line on the module */
    virtual void performClockHigh();
    virtual void performClockLow();

    /** Updates the control lines on the module */
    virtual void performUpdateLines();

    virtual void performRegisterControlLines(IInstructionController &ptrIC);

public:

    void Reset();
    void ClockHigh();
    void ClockLow();
    void UpdateLines();
    void RegisterControlLines(IInstructionController &ptrIC);
};

