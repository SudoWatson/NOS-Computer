#pragma once

class IRegisterController {
public:
    virtual bool* GetRegisterInControlLinePtr() = 0;
    virtual bool* GetRegisterIncrementLinePtr() = 0;
    virtual bool* GetRegisterDecrementLinePtr() = 0;
};
