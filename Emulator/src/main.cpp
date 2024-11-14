// src/main.cpp
#include "../headers/Bus.h"
#include "../headers/RegisterController.h"
#include "../headers/ALU.h"
#include "InstructionController.h"
#include <cstdint>
#include <iostream>

#define log(x) std::cout << x << std::endl

class valueHolder {
public:
    uint16_t value;
};

int main() {
    valueHolder inputValue;
    inputValue.value = 5;

    Bus mainBus;
    Bus lhBus;
    Bus rhBus;


    InstructionController ic(mainBus);
    ic.RegisterControlLines(ic);

    ALU alu(mainBus, lhBus, rhBus);
    alu.RegisterControlLines(ic);

    RegisterController rc(mainBus, lhBus, rhBus);
    rc.RegisterControlLines(ic);


    ic.Reset();

    // Load instruction 0
    inputValue.value = 0x000;
    mainBus.Assert(&inputValue.value);
    ic.ClockHigh();
    alu.ClockHigh();
    rc.ClockHigh();
    mainBus.UnAssert(&inputValue.value);

    // Index register 0
    inputValue.value = 0x000;
    mainBus.Assert(&inputValue.value);
    ic.ClockHigh();
    alu.ClockHigh();
    rc.ClockHigh();
    mainBus.UnAssert(&inputValue.value);

    // Load instruction 1
    inputValue.value = 0x001;
    mainBus.Assert(&inputValue.value);
    ic.ClockHigh();
    alu.ClockHigh();
    rc.ClockHigh();
    mainBus.UnAssert(&inputValue.value);

    // Load value into register
    inputValue.value = 0xF08B;
    mainBus.Assert(&inputValue.value);
    ic.ClockHigh();
    alu.ClockHigh();
    rc.ClockHigh();
    mainBus.UnAssert(&inputValue.value);

    // Load instruction 2
    inputValue.value = 0x002;
    mainBus.Assert(&inputValue.value);
    ic.ClockHigh();
    alu.ClockHigh();
    rc.ClockHigh();
    mainBus.UnAssert(&inputValue.value);

    // Read back value from register
    ic.ClockHigh();
    alu.ClockHigh();
    rc.ClockHigh();

    return 0;
}

