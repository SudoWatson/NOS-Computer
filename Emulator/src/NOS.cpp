#include "iostream"
#include "vector"
#include "list"

#include "CPU.h"


int main() {
    CPU cpu = CPU();
    std::cout << cpu.toString();
    cpu.RC.AReg.setValue(30);
    cpu.RC.BReg.setValue(12);
    cpu.RC.RCIn(0b00000110);
    cpu.execute(0b0000);
    std::cout << cpu.toString();
    return 0;
}

/*


struct CPU {

    ALU alu;
    Mem memory;
    RegisterController regCont;
    InstructionController instCont


}

struct instCont {
    CPU *cpu

    void registerInstruction(instruction, instructionName)
    []keys;
    []vals;

    getInstruction(key) {
        i = keys.indexOf(key)
        return vals[i]
    }

    void execute(instruction) {
        if first4BitsMatchALU {
            cpu->alu.execute(instruction)
        }
    }
}

struct RegisterController {
    Register Areg;
    Register Breg;
    Register Creg;
    Register Dreg;
}

struct ALU {
    void execute(instruction) {
        Last4bits tell instruction
        Get next Byte in memory
            First 2 bits are ignored
            Next 2 bits are lefthand reg
            Next are righthand
            Next are output
    }
}


CPU

CPU has register controller
CPU has registers
CPU has an ALU
CPU has Memory


*/