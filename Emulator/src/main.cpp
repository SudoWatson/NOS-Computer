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


    int loadRegControllerInst = 0;
    int registerInInst = 1;
    int bypassRegisterOutInst = 2;
    int aluInstructionInInst = 3;
    int aluResultOutInst = 4;


    // Load 1 into register 0
    // Load 2 into register 1
    // Load add command into ALU
    // ALU result into register 2
    // Read result of register 2


    // Load 2 into register 1
    // Load loadRegCont instruction
    inputValue.value = 0x1002;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);


    // Execute loadRegCont instruction
    inputValue.value = 0x0008;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);

    // Load 2 into register 1
    // Load loadRegCont instruction
    inputValue.value = 0x1001;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);

    // Execute loadRegCont instruction
    inputValue.value = 0x0005;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);

    // Calculate ALU of reg 0 + reg 1 into register 2
    // Load loadRegCont instruction
    inputValue.value = loadRegControllerInst;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);

    // Execute loadRegCont instruction
    inputValue.value = 0x0210;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    mcc.FullCycle();

    // Load aluInstIn instruction
    inputValue.value = aluInstructionInInst;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);

    // Execute aluInstIn instruction
    inputValue.value = 0x0000;  // Add without carry
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);
    mcc.FullCycle();


    // Load Read ALU result
    inputValue.value = aluResultOutInst;
    mainBus.Assert(&inputValue.value);
    mcc.FullCycle();
    mainBus.UnAssert(&inputValue.value);

    // Read ALU result
    std::cout << *mainBus.GetValue() << std::endl;


    return 0;
}

