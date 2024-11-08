// src/main.cpp
#include "../../headers/Bus.h"
#include "../../headers/RegisterController.h"
#include "../../headers/IHasValue.h"
#include <iostream>


/**
* This tests propery functionality for the Register Controller changing between registers.
* It first sets a value to it's initial register
* Then switches to a different register and sets its value
* Then switches back to the original register
*/
int main() {
    IHasValue inputValue;
    inputValue.value = 5;

    Bus mainBus;
    Bus lhBus;
    Bus rhBus;


    std::cout << "Register Value: " << rhBus.GetValue() << std::endl; // 0 - Not dereferencing because it's nullptr
    RegisterController rc(mainBus, lhBus, rhBus);

    // 5 to bus and into selected (0) register
    mainBus.AssertFrom(&inputValue);
    rc.LoadFromMainBusToRegister();
    mainBus.UnAssertFrom(&inputValue);
    std::cout << "Register Value: " << *rhBus.GetValue() << std::endl;  // 5

    // 0 1 1 to bus and into RC
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

    // 0 0 0 to bus and into RC
    inputValue.value = 0x000;
    mainBus.AssertFrom(&inputValue);
    rc.LoadFromMainBus();
    mainBus.UnAssertFrom(&inputValue);
    std::cout << "Register Value: " << *rhBus.GetValue() << std::endl;  // 5
    return 0;
}

