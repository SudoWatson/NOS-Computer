#pragma once

class IRegisterController {
public:
    virtual bool* GetRegisterInControlLinePtr() = 0;
};
