#include "CPU.h"

CPU::CPU() {
    int AddresBusSize = 3;
    PC   = AdrReg(AddresBusSize);       // Program Counter
    MAR  = AdrReg(AddresBusSize);       // Memory Address Register
    Inst = Reg();                       // Instruction Register
    alu  = ALU(this);                    // Arithmetic & Logic Unit
    RC   = new RegisterController(this);    // Register Controller
}

std::string CPU::toString() {
    std::string string = "";
    string += "CPU STATUS\n";
    string += RC->toString();
    string += "\n\n--ADDRESS REGISTERS--\n";
    // string += "PC:  " + PC.toString();
    // string += "MAR: " + MAR.toString();
    return string;
}
