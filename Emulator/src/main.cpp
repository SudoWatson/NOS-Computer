// src/main.cpp
#include "../headers/Bus.h"
#include "../headers/RegisterController.h"
#include "../headers/ALU.h"
#include "../headers/IHasValue.h"
#include <iostream>


int main() {
    IHasValue inputValue;
    inputValue.value = 5;

    Bus mainBus;
    Bus lhBus;
    Bus rhBus;

    RegisterController rc(mainBus, lhBus, rhBus);

    ALU alu(mainBus, lhBus, rhBus);

    // 5 to bus and into selected (0) register
    mainBus.AssertFrom(&inputValue);
    rc.LoadFromMainBusToRegister();
    mainBus.UnAssertFrom(&inputValue);
    std::cout << "Register Value: " << *rhBus.GetValue() << std::endl;  // 5

    // 0 1 2 to bus and into RC
    inputValue.value = 0x011;
    mainBus.AssertFrom(&inputValue);
    rc.LoadFromMainBus();
    mainBus.UnAssertFrom(&inputValue);
    std::cout << "Register Value: " << *rhBus.GetValue() << std::endl;  // 0

    // 8 to bus and into selected (1) register
    inputValue.value = 8;
    mainBus.AssertFrom(&inputValue);
    rc.LoadFromMainBusToRegister();
    mainBus.UnAssertFrom(&inputValue);
    std::cout << "Register Value: " << *rhBus.GetValue() << std::endl;  // 8

    // 0 1 2 to bus and into RC
    inputValue.value = 0x012;
    mainBus.AssertFrom(&inputValue);
    rc.LoadFromMainBus();
    mainBus.UnAssertFrom(&inputValue);
    std::cout << "Register Value: " << *rhBus.GetValue() << std::endl;  // 0

    std::cout << std::endl;
    // Load ALU into 3
    alu.AssertToMainBus();
    rc.LoadFromMainBusToRegister();
    std::cout << "Main Bus Value: " << *mainBus.GetValue() << std::endl;  // 13
    alu.UnAssertToMainBus();
    std::cout << "Right Hand Register Value: " << *rhBus.GetValue() << std::endl;  // 8
    std::cout << std::endl;

    // 0 2 0 to bus and into RC
    inputValue.value = 0x020;
    mainBus.AssertFrom(&inputValue);
    rc.LoadFromMainBus();
    mainBus.UnAssertFrom(&inputValue);
    std::cout << "Register Value: " << *rhBus.GetValue() << std::endl;  // 13

    // 0 0 0 to bus and into RC
    inputValue.value = 0x000;
    mainBus.AssertFrom(&inputValue);
    rc.LoadFromMainBus();
    mainBus.UnAssertFrom(&inputValue);
    std::cout << "Register Value: " << *rhBus.GetValue() << std::endl;  // 5

    return 0;
}

