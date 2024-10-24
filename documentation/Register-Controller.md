This part is what controls the various registers of the Nos computer. It takes a 12-bit input to determine what registers follow its instructions. The left 4 index the register for the left hand bus, the middle 4 for the right hand bus, and the right 4 for the main bus (verify this true?). The register controller is able to control up to 15 [General Purpose Registers](documentation/General-Purpose-Registers.md), and the 4 [[Special Purpose Registers]]. 




### Going with the always bypass through ALU method. Register OE line is now "Output to main bus instead of RHB" note on [ALU](documentation/ALU.md) has this note as well


#### Thoughts, need to be properly documented
GPR register 0000 can't exist
2 lines to index the SPR
1 line to say "Hey use the SPR instead of the GPR"
2 lines to say "Hey SPR ## output somewhere". 0 register not have this ability. 0 will be the natural off state of this to avoid having another line for it. Just don't connect register 0 to this and it should work

##### To move GPR to GPR
Move out GPR to RHBus, In GPR to Register Enable
> ALU should have a "Bypass out" flag, or, registers should have a "right hand output actually means regular output" line absolutely 0 thought but leaning towards option B although 1 thought provides that adding the ALU bypass could possibly remove the need for possible separation of the RHOut and the regular Out, dropping some needed bits by 33.3̅% but another half thought worries that interferes with Move GPR to SPR rules

Somehow bypass register to output onto the main bus (either via ALU or bypass line) and load into register
Move

##### To move SPR into SPR
2 lines indexed to the input register, 1 line set to SPR mode, 2 lines set to output register (00 not an option)
Move

##### To move SPR into GPR
Move in GPR to register enable
1 line set to GPR mode, 2 lines set to output SPR register (not dependent on the mode line)
Move

##### To move GPR to SPR
Move out GPR to righthand out, 2 lines indexed to SPR, 1 line set to SPR, somehow bypass register to output onto main bus
Move