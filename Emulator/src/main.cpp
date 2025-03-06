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


    mcc.FullCycle();
    mcc.FullCycle();
    mcc.FullCycle();
    mcc.FullCycle();
    mcc.FullCycle();
    mcc.FullCycle();
    mcc.FullCycle();
    mcc.FullCycle();
    mcc.FullCycle();
    mcc.FullCycle();
    mcc.FullCycle();
    mcc.FullCycle();
    mcc.FullCycle();
    mcc.FullCycle();
    mcc.FullCycle();
    mcc.FullCycle();
    mcc.FullCycle();
    mcc.FullCycle();
    mcc.FullCycle();
    mcc.FullCycle();
    mcc.FullCycle();
    mcc.FullCycle();
    mcc.FullCycle();
    mcc.FullCycle();
    mcc.FullCycle();
    mcc.FullCycle();
    mcc.FullCycle();
    mcc.FullCycle();
    mcc.FullCycle();
    mcc.FullCycle();
    mcc.FullCycle();


    return 0;
}

