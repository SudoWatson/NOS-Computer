// src/main.cpp
#include "../headers/Bus.h"
#include "../headers/RegisterController.h"
#include "../headers/ALU.h"
#include "InstructionController.h"
#include "ModuleCommonControl.h"
#include <cstdint>
#include <iostream>

#define log(x) std::cout << x << std::endl

class valueHolder {
public:
    valueHolder(uint16_t _value=0) {value = _value;}
    uint16_t value;
};

int main() {
    valueHolder inputValue;

    Bus mainBus;
    Bus lhBus;
    Bus rhBus;


    ModuleCommonControl mcc;

    InstructionController ic(mainBus);
    mcc.AddModule(&ic);

    ALU alu(mainBus, lhBus, rhBus);
    mcc.AddModule(&alu);

    RegisterController rc(mainBus, lhBus, rhBus);
    mcc.AddModule(&rc);

    mcc.ConnectControlLines(ic);

    mcc.Reset();


    // Load 2 into register 1
    inputValue.value = 0x1001;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    inputValue.value = 0x0000;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);

    // Load 2 into register 2
    inputValue.value = 0x1002;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    inputValue.value = 0x0001;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);

    for (int i = 0; i < 255; i++)
    {

        // Calculate ALU of reg 0 + reg 1 into register 2
        inputValue.value = 0x0123;  // Sub reg 1 - 2 into 3
        mainBus.Assert(&inputValue.value);
        mcc.FullCycle();
        mcc.FullCycle();
        mainBus.UnAssert(&inputValue.value);
        mcc.FullCycle();

        // Move reg 2 to 1
        inputValue.value = 0x3021;
        mainBus.Assert(&inputValue.value);
        mcc.FullCycle();
        mcc.FullCycle();
        mainBus.UnAssert(&inputValue.value);
        mcc.FullCycle();

        // Move reg 3 to 2
        inputValue.value = 0x3032;
        mainBus.Assert(&inputValue.value);
        mcc.FullCycle();
        mcc.FullCycle();
        mainBus.UnAssert(&inputValue.value);
        mcc.FullCycle();

        // Read Register result
        inputValue.value = 0x2010;
        mainBus.Assert(&inputValue.value);
        mcc.FullCycle();
        mcc.FullCycle();
        mainBus.UnAssert(&inputValue.value);
        std::cout << "Cycle " << i << ": " << *mainBus.GetValue() << std::endl;
        mcc.FullCycle();
    }

    return 0;
}

