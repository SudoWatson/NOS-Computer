> [!WARNING]
> A lot of the following documentation has not been updated and is not correct.
> The biggest inaccuracy is the instruction definitions in the ALU documentation

"Nos" is a 16-Bit computer created with off the shelf components. It comprises of:
- 16-bit bus for both data and addresses
- [ALU](documentation/ALU.md)
- [Instruction Controller](documentation/Instruction-Controller.md)
- A [Register Controller](documentation/Register-Controller.md) that can control:
	- Up to 15 16-Bit [General Purpose Registers](documentation/General-Purpose-Registers.md)
	- Program Counter
	- Instruction Pointer
	- RAM Pointer
	- Stack Pointer


# Emulator Development
Run the Emulator/build.sh script. This will build the project into Emulator/build resulting in a `NOSComputerEmulator` executable. The script will also run the exec.
After building, in NeoVim you can use the DAP to debug. Pressing F1 will start the debugger. You'll need to type the path to the executable that was built.
After doing this once, next time you debug you can just hit the up error to get previous path
