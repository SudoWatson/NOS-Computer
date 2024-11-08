// src/main.cpp
#include "../headers/GPR.h"
#include "../headers/Bus.h"
#include "../headers/IHasValue.h"
#include <iostream>


int main() {
    Bus bus;

    GPR gpr;
    gpr.MainBus = &bus;
    gpr.AssertToMainBus();
    std::cout << "GPR Value: " << bus.ReadValue() << std::endl;
    gpr.UnAssertToMainBus();

    IHasValue valueTest;
    valueTest.value = 10;
    bus.AssertFrom(&valueTest);
    gpr.LoadFromMainBus();
    bus.UnAssertFrom(&valueTest);

    gpr.AssertToMainBus();
    std::cout << "GPR Value: " << bus.ReadValue() << std::endl;
    gpr.UnAssertToMainBus();


    std::cin.get();
    return 0;
}

