// src/main.cpp
#include "../headers/Bus.h"
#include "../headers/RegisterController.h"
#include "../headers/IHasValue.h"
#include <iostream>


int main() {
    IHasValue inputValue;
    inputValue.value = 5;

    Bus mainBus;
    Bus lhBus;
    Bus rhBus;


    std::cout << "Register Value: " << rhBus.ReadValue() << std::endl; // 0
    RegisterController rc(mainBus, lhBus, rhBus);

    // 5 to bus and into selected (0) register
    mainBus.AssertFrom(&inputValue);
    rc.LoadFromMainBusToRegister();
    mainBus.UnAssertFrom(&inputValue);
    std::cout << "Register Value: " << rhBus.ReadValue() << std::endl;  // 5

    // 0 1 1 to bus and into RC
    inputValue.value = 0x011;
    mainBus.AssertFrom(&inputValue);
    rc.LoadFromMainBus();
    mainBus.UnAssertFrom(&inputValue);
    std::cout << "Register Value: " << rhBus.ReadValue() << std::endl;  // 0

    // 8 to bus and into selected (1) register
    inputValue.value = 8;
    mainBus.AssertFrom(&inputValue);
    rc.LoadFromMainBusToRegister();
    mainBus.UnAssertFrom(&inputValue);
    std::cout << "Register Value: " << rhBus.ReadValue() << std::endl;  // 8

    // 0 0 0 to bus and into RC
    inputValue.value = 0x000;
    mainBus.AssertFrom(&inputValue);
    rc.LoadFromMainBus();
    mainBus.UnAssertFrom(&inputValue);
    std::cout << "Register Value: " << rhBus.ReadValue() << std::endl;  // 5

    std::cin.get();
    return 0;
}

