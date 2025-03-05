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


    // Not actually loading value. Need to see why
    // Load into SPR
    inputValue.value = 0x0000;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    inputValue.value = 0x0015;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    mcc.FullCycle();

    // Load into SPR
    inputValue.value = 0x0001;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    inputValue.value = 0x0034;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    mcc.FullCycle();

    // Load into SPR
    inputValue.value = 0x0002;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    inputValue.value = 0x0084;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    mcc.FullCycle();

    // Load into SPR
    inputValue.value = 0x0003;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    inputValue.value = 0x0672;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    mcc.FullCycle();

    return 0;
}

