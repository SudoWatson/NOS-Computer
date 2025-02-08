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


    // Load instruction 0
    inputValue.value = 0x000;
    mainBus.Assert(&inputValue.value);
    mcc.ClockHigh();
    mcc.ClockLow();
    mcc.UpdateLines();
    mainBus.UnAssert(&inputValue.value);

    // Index register 0
    inputValue.value = 0x000;
    mainBus.Assert(&inputValue.value);
    mcc.ClockHigh();
    mcc.ClockLow();
    mcc.UpdateLines();
    mainBus.UnAssert(&inputValue.value);

    // Load instruction 1
    inputValue.value = 0x001;
    mainBus.Assert(&inputValue.value);
    mcc.ClockHigh();
    mcc.ClockLow();
    mcc.UpdateLines();
    mainBus.UnAssert(&inputValue.value);

    // Load value into register
    inputValue.value = 0xF08B;
    mainBus.Assert(&inputValue.value);
    mcc.ClockHigh();
    mcc.ClockLow();
    mcc.UpdateLines();
    mainBus.UnAssert(&inputValue.value);

    // Load instruction 2
    inputValue.value = 0x002;
    mainBus.Assert(&inputValue.value);
    mcc.ClockHigh();
    mcc.ClockLow();
    mcc.UpdateLines();
    mainBus.UnAssert(&inputValue.value);

    // Read back value from register
    mcc.ClockHigh();
    mcc.ClockLow();
    mcc.UpdateLines();

    std::cout << *mainBus.GetValue() << std::endl;


    return 0;
}

