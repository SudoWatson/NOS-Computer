// src/main.cpp
#include "CPU.h"
#include <cstdint>
#include <iostream>
#include <ostream>

#define log(x) std::cout << x << std::endl

class valueHolder {
public:
    valueHolder(uint16_t _value=0) {value = _value;}
    uint16_t value;
};

#define runInstruction() cpu.FullCycle();cpu.FullCycle();cpu.FullCycle();cpu.FullCycle();cpu.FullCycle();cpu.FullCycle();cpu.FullCycle();

int main() {

    CPU cpu;
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

