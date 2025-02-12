// src/main.cpp
#include "../headers/Bus.h"
#include "../headers/RegisterController.h"
#include "../headers/ALU.h"
#include "InstructionController.h"
#include "ModuleCommonControl.h"
#include <cstdint>
#include <iostream>
#include <ostream>

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


    // Load value into reg 0
    inputValue.value = 0x1000;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    inputValue.value = 0b1000000000011011;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);

    
    // 1000 00DC and 01DC for Rotate and Shift

    // Rotate Left 0 into 1
    inputValue.value = 0x8001;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    mcc.FullCycle();

    // Rotate Right 0 into 2
    inputValue.value = 0x8202;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    mcc.FullCycle();

    // Shift Left 0 into 3
    inputValue.value = 0x8403;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    mcc.FullCycle();

    // Shift Right 0 into 4
    inputValue.value = 0x8604;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    mcc.FullCycle();


    std::cout << "Register Values:" << std::endl;
    for (int i = 0; i < 16; i++)
    {
        std::cout << "Register " << i << ": ";
        // Read register value
        inputValue.value = 0x2000 | (i << 4);
        mainBus.Assert(&inputValue.value);
        mcc.FullCycle();
        mcc.FullCycle();
        mainBus.UnAssert(&inputValue.value);
        std::cout << *mainBus.GetValue() << std::endl;
        mcc.FullCycle();
    }


    return 0;
}

