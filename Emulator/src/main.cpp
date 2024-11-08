// src/main.cpp
#include "GPR.h"
#include "Bus.h"
#include "IHasValue.h"
#include <iostream>


int main() {
    Bus bus;

    GPR gpr;
    gpr.setValue(5);
    gpr.mainBus = &bus;
    std::cout << "GPR Value: " << gpr.getValue() << std::endl;

    IHasValue valueTest;
    valueTest.value = 10;
    bus.AssertTo(&valueTest);
    gpr.load();
    bus.UnAssertSelf(&valueTest);
    std::cout << "GPR Value: " << gpr.getValue() << std::endl;


    std::cin.get();
    return 0;
}

