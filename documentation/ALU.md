The Arithmetic Logic Unit takes in a full 16-Bit input on both the left and right hand side to perform one of several arithmetic or logical operations, pushing the result onto the main bus.

The possible arithmetic operations are
- Add
- Subtract

The possible logical operations are
- And
- Or
- Xor
- Not
- The Not version of all of the above
- Shifts
- Rotates

The ALU gets its inputs from the Left Hand Bus and the Right Hand Bus from the registers. Which registers go to which bus is determined by the [Register Controller](documentation/Register-Controller.md). Any operations that uses a single input (Not, Shifts, Rotates) will use the Right Hand Bus and anything on the Left Hand Bus will be ignored.

The ALU takes in a 5 bit instruction. The left-most bit puts the ALU into arithmetic (0) or logic (1) mode, where the remaining 4 bits determine what operation is done depending on the mode.
#### Instructions
<table>
    <tr>
        <td colspan="5" align="center">Bits</td>
    </tr>
    <tr>
        <td>5</td>
        <td>4</td>
        <td>3</td>
        <td>2</td>
        <td>1</td>
    </tr>
    <tr>
        <td rowspan="2">(0) Arithmetic</td>
        <td rowspan="2" colspan="2">Unused</td>
        <td>(0) Add</td>
        <td rowspan="2">Use CarryIn Flag</td>
    </tr>
    <tr>
        <td>(1) Subtract</td>
    </tr>
    <tr>
        <td rowspan="3">(1) Logic</td>
        <td>(0) Bitwise Mode</td>
        <td>Invert Result</td>
        <td colspan="2">Operation Instruction*</td>
    </tr>
    <tr>
        <td rowspan="2">(1) Shift Mode</td>
        <td>(0) Rotate</td>
        <td rowspan="2">Direction (0 - Left?)</td>
        <td rowspan="2">Use Carry </td>
    </tr>
    <tr>
        <td>(1) Logical Shift</td>
    </tr>
</table>

##### Bitwise Operations
| Bit 2 | Bit 1 | Operation                                 |
| ----- | ----- | ----------------------------------------- |
| 0     | 0     | None (Use with Bit 3 to invert the input) |
| 0     | 1     | And                                       |
| 1     | 0     | Or                                        |
| 1     | 1     | Xor                                       |

### Explanation of Inputs

| Pin | Name                  | Use                                                                                                                        |
| --- | --------------------- | -------------------------------------------------------------------------------------------------------------------------- |
| LH# | Left Hand Pin #       |                                                                                                                            |
| RH# | Right Hand Pin #      |                                                                                                                            |
| ∑I  | ALU Instruction In    | Loads the instruction for the ALU from the main bus (∑ is the symbol for the ALU because I want it to be)                  |
| ∑#  | ALU Instruction #     | Pins for input from the main bus to the internal instruction register                                                      |
| ∑O  | Result Out            |                                                                                                                            |
| BRO | Bypass Right Hand Out | Bypasses the ALU to output the Right Hand Bus. This is used by the Register Controller to transfer a register into another |
| CI  | Carry In              | Carry In flag                                                                                                              |
| CLK | Clock                 |                                                                                                                            |
