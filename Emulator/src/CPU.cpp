#include "CPU.h"

CPU::CPU() {
    int AddresBusSize = 3;
    PC   = AdrReg(AddresBusSize);       // Program Counter
    MAR  = AdrReg(AddresBusSize);       // Memory Address Register
    Inst = Reg();                       // Instruction Register
    alu  = ALU(this);                   // Arithmetic & Logic Unit
    RC   = RegisterController(this);    // Register Controller
}

std::string CPU::toString() {
    std::string string = "";
    string += "\n\n\nCPU STATUS\n\n";
    string += RC.toString();
    string += "\n--ADDRESS REGISTERS--\n";
    string += "PC:  " + PC.toString() + "\n";
    string += "MAR: " + MAR.toString() + "\n";
    return string;
}

void CPU::execute(Byte instruction) {
    alu.loadInstruction(instruction);
    alu.execute();
}
