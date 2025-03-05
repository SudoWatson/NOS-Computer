// src/main.cpp
#include "../headers/ALU.h"
#include "../headers/Bus.h"
#include "../headers/RAM.h"
#include "../headers/RegisterController.h"
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
    Bus marBus;


    ModuleCommonControl mcc;

    InstructionController ic(mainBus);
    mcc.AddModule(&ic);

    ALU alu(mainBus, lhBus, rhBus);
    mcc.AddModule(&alu);

    RegisterController rc(mainBus, lhBus, rhBus, marBus);
    mcc.AddModule(&rc);

    RAM ram(mainBus, marBus);
    mcc.AddModule(&ram);

    mcc.ConnectControlLines(ic);

    mcc.Reset();
    mcc.UpdateLines();


    // This one works
    // Load into Register
    inputValue.value = 0x2001;
    mcc.FullCycle();
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    mcc.FullCycle();
    inputValue.value = 0xA675;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    mcc.FullCycle();

    // This is loading 2 into the GPR for some reason. Also loading 0 before hand for some reason
    // Load into Register
    inputValue.value = 0x0001;
    mcc.FullCycle();
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    mcc.FullCycle();
    inputValue.value = 0x0002;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    mcc.FullCycle();

    // Load into Register
    inputValue.value = 0x1002;
    mcc.FullCycle();
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    mcc.FullCycle();
    inputValue.value = 0x0002;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    mcc.FullCycle();


    return 0;
}

