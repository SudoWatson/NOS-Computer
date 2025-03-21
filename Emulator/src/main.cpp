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

#define runInstruction() mcc.FullCycle();mcc.FullCycle();mcc.FullCycle();mcc.FullCycle();mcc.FullCycle();mcc.FullCycle();mcc.FullCycle();

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


    /*
     * Figuring out the instructions
     * For the immediate load, I need to increment the Program Counter a second time somewhere in the instruction set
     * hopefully without making an entire step for it
        *
        */

    // Setup
    runInstruction();
    runInstruction();

    for (int i = 0; i < 1000; i++)
    {
        // Adds
        runInstruction();
        runInstruction();

        // Jump
        runInstruction();
    }


    return 0;
}

