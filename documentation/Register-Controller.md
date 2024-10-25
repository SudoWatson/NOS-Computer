This part is what controls the various registers of the Nos computer. It takes a 12-bit input to determine what registers follow its instructions. The left 4 index the register for the left hand bus, the middle 4 for the right hand bus, and the right 4 for the main bus (verify this true?). The register controller is able to control up to 15 [General Purpose Registers](documentation/General-Purpose-Registers.md), and the 4 [[Special Purpose Registers]]. 




### Going with the always bypass through ALU method. Register OE line is now "Output to main bus instead of RHB" note on [ALU](documentation/ALU.md) has this note as well


#### Thoughts, need to be properly documented
GPR register 0000 can't exist
2 lines to index the SPR
1 line to say "Hey use the SPR instead of the GPR"
1 line on the ALU to Bypass Right Hand Bus Out (BRO pin)
2 lines to say "Hey SPR ## output somewhere". 00 register not have this ability. 00 will be the natural off state of this to avoid having another line for it. Just don't connect register 00 to this and it should work
Should be able to wire both lines just like normal GPR. Should be able to just use GPRs for this

### Explanation of Instructions for Moves
##### To move GPR to GPR
Move out GPR to RHBus, In GPR to Register Enable
BRO on and load into register; Move

##### To move SPR into SPR
2 lines indexed to the input register, 1 line set to SPR mode, 2 lines set to output register (00 not an option)
Move

##### To move SPR into GPR
Move in GPR to register enable
1 line set to GPR mode, 2 lines set to output SPR register (not dependent on the mode line)
Move

##### To move GPR to SPR
Move out GPR to right hand out
2 lines indexed to SPR, 1 line set to SPR, BRO on; Move


## Explanation of Inputs

| Pin    | Name                   | Use                                                                                                                                     |
| ------ | ---------------------- | --------------------------------------------------------------------------------------------------------------------------------------- |
| CLK    | Clock line             | -                                                                                                                                       |
| R̅C̅I̅ | Register Controller In | Stores the contents of the bus in the internal register for indexing the registers                                                      |
| CRM    | Crement                | To perform an in/decrement operation. Which one it does is determined by the 5th bit from the right, next to the regular register index |
| RES    | Reset                  | Resets all registers including the internal register                                                                                    |
| B#     | Bus Bit # In           | Pins connecting to the main bus for input                                                                                               |
