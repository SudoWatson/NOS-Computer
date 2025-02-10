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
    inputValue.value = 0b00011011;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);

    // Load value into reg 1
    inputValue.value = 0x1001;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    inputValue.value = 0b01001101;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);

    // ALU Logic Tests
    inputValue.value = 0x8812;  // Pass through register 1 into 2 (Bitwise no operation)
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    mcc.FullCycle();

    // AND
    inputValue.value = 0x9013;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    mcc.FullCycle();

    // OR
    inputValue.value = 0xA014;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    mcc.FullCycle();

    // XOR
    inputValue.value = 0xB015;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    mcc.FullCycle();

    // NOT
    inputValue.value = 0xC816;  // Not register 1 into 2
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    mcc.FullCycle();

    // NAND
    inputValue.value = 0xD017;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    mcc.FullCycle();

    // NOR
    inputValue.value = 0xE018;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    mcc.FullCycle();

    // XNOR
    inputValue.value = 0xF019;
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

