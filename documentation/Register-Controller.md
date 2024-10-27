This part is what controls the various registers of the Nos computer. The register controller is able to control up to 15 [General Purpose Registers](documentation/General-Purpose-Registers.md), and the main 4 [[Special Purpose Registers]] (Program Counter, Instruction Register, Memory Access Register, and Stack Pointer). It takes a 12-bit input to determine what GPR follows its instructions. The left 4 index the register for the left hand bus, the middle 4 for the right hand bus/output register, and the right 4 for the main bus (verify this true?). There is an instruction line to signal to use the SPRs instead, which leads the RC to use 2 instruction lines to index which SPR follows the instruction. There are 2 other instruction lines to index which SPR to push to the bus (SPR 00, the MAR, is not indexible as 00 is treated as no output) which ignores the SPR enable line. There is also a line to bypass the register set to the RHB to output to the main bus through the ALU instaed. This is to enable cross-register movements which are desrcibed below (idk how to link and am just typing rn).




### Going with the always bypass through ALU method. Register OE line is now "Output to main bus instead of RHB" note on [ALU](documentation/ALU.md) has this note as well
2 lines to say "Hey SPR ## output somewhere". 00 register not have this ability. 00 will be the natural off state of this to avoid having another line for it. Just don't connect register 00 to this and it should work
Should be able to wire both lines just like normal GPR. Should be able to just use GPRs for this

### Explanation of Register to Register Moves
##### GPR-GPR
Move (out GPR) to RHBus, (In GPR) to Register Enable
BRO on and load into register; Move

##### SPR-SPR
2 lines indexed to the input SPR, 1 line set to SPR mode, 2 lines set to output SPR (00 not an option)
Move

##### SPR-GPR
Move (in GPR) to register enable
1 line set to GPR mode, 2 lines set to output SPR register (not dependent on the mode line)
Move

##### GPR-SPR
Move out GPR to right hand out
2 lines indexed to SPR, 1 line set to SPR, BRO on; Move


## Explanation of Inputs

| Pin                                                | Name                   | Use                                                                                                                                     |
| -------------------------------------------------- | ---------------------- | --------------------------------------------------------------------------------------------------------------------------------------- |
| CLK                                                | Clock line             | -                                                                                                                                       |
| <span style="text-decoration: overline">RCI</span> | Register Controller In | Stores the contents of the bus in the internal register for indexing the registers                                                      |
| CRM                                                | Crement                | To perform an in/decrement operation. Which one it does is determined by the 5th bit from the right, next to the regular register index |
| RES                                                | Reset                  | Resets all registers including the internal register                                                                                    |
| B#                                                 | Bus Bit # In           | Pins connecting to the main bus for input                                                                                               |
| SPR                                                | Use SPRs               | This will index the SPRs instead of the GPRs. The RHB, LHB, and SPROut are not affected by this.                                        |
