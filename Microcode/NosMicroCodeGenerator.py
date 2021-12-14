import sys

print("\n\n\n\n")

# MicroCode Generator for Nos Computer
filePath = "C:/Users/aulen/Desktop/Things/Tools/Logisim/UpdCPU/Microcode/"  # Leave empty for current path

baseFileName = "NosMicroCode"
fileName = filePath + baseFileName


#  Microcode Word
#  HLT DSC NA NA NA RCI RI RO RUC CRM BRO IID DID IDI OUT8 IN8 FLOD IR ADR RSR MAR PC PCO GR GRO RMO RMI IRI IRO SCR FSI SF CF LF FO DFI EO EII PSH POP IOI IOO IDO SID
wordLength = 44


HLT  = 0b10000000000000000000000000000000000000000000
DSC  = 0b01000000000000000000000000000000000000000000
NA   = 0b00100000000000000000000000000000000000000000
NA   = 0b00010000000000000000000000000000000000000000

NA   = 0b00001000000000000000000000000000000000000000
RCI  = 0b00000100000000000000000000000000000000000000
RI   = 0b00000010000000000000000000000000000000000000
RO   = 0b00000001000000000000000000000000000000000000
RUC  = 0b00000000100000000000000000000000000000000000
CRM  = 0b00000000010000000000000000000000000000000000
BRO  = 0b00000000001000000000000000000000000000000000
IID  = 0b00000000000100000000000000000000000000000000

DID  = 0b00000000000010000000000000000000000000000000
IDI  = 0b00000000000001000000000000000000000000000000
OUT8 = 0b00000000000000100000000000000000000000000000
IN8  = 0b00000000000000010000000000000000000000000000
FLOD = 0b00000000000000001000000000000000000000000000
IR   = 0b00000000000000000100000000000000000000000000
ADR  = 0b00000000000000000010000000000000000000000000
RSR  = 0b00000000000000000001000000000000000000000000

MAR  = 0b00000000000000000000100000000000000000000000
PC   = 0b00000000000000000000010000000000000000000000
PCO  = 0b00000000000000000000001000000000000000000000
GR   = 0b00000000000000000000000100000000000000000000
GRO  = 0b00000000000000000000000010000000000000000000
RMO  = 0b00000000000000000000000001000000000000000000
RMI  = 0b00000000000000000000000000100000000000000000
IRI  = 0b00000000000000000000000000010000000000000000

IRO  = 0b00000000000000000000000000001000000000000000
SCR  = 0b00000000000000000000000000000100000000000000
FSI  = 0b00000000000000000000000000000010000000000000
SF   = 0b00000000000000000000000000000001000000000000
CF   = 0b00000000000000000000000000000000100000000000
LF   = 0b00000000000000000000000000000000010000000000
FO   = 0b00000000000000000000000000000000001000000000
DFI  = 0b00000000000000000000000000000000000100000000

EO   = 0b00000000000000000000000000000000000010000000
EII  = 0b00000000000000000000000000000000000001000000
PSH  = 0b00000000000000000000000000000000000000100000
POP  = 0b00000000000000000000000000000000000000010000
IOI  = 0b00000000000000000000000000000000000000001000
IOO  = 0b00000000000000000000000000000000000000000100
IDO  = 0b00000000000000000000000000000000000000000010
SID  = 0b00000000000000000000000000000000000000000001


activeLow = HLT|DSC|BRO

#  DSC CONTROL LINE Sends Instruction Register into constant loop of moving data from RAM to Address Register 8 bits at a time. Continues until all registers finished.


uniqueInstructions =  0
instructionCount =  0
def newInst(low, high, value):
    global uniqueInstructions
    global instructionCount
    if not (value == NOP):
        uniqueInstructions += 1
    for n in range(high+1-low):
        instructions[low+n] = list(FetchCycle)
        instructions[low+n].extend(value)
        if not (value == NOP):
            instructionCount += 1

#             PCO out to MAR.   RAM to IR. Inc PC
FetchCycle = [PCO|MAR|FLOD,     RMO|IRI|PC|IR]
instructions = [0 for x in range(256)]  # 256 different instructions all beginning with the Fetch Cycle

# Define Instructions                               14 steps  (14 steps + 2 fetch steps = 16 steps)
NOP = [0,                   0,              0,              0,              0,                  0,              0,      0, 0, 0, 0, 0, 0, 0]  # No Op
LDI = [PC|MAR|IR|IRO|RCI,   RMO|RI,         SCR,            0,              0,                  0,              0,      0, 0, 0, 0, 0, 0, 0]  # Load Immediate
LOD = [PC|MAR|IR|IRO|RCI,   RMO|GR|IDI,     DSC,            GRO|MAR|FLOD,   RMO|RI|GR|IID,      SCR,            0,      0, 0, 0, 0, 0, 0, 0]  # Load Address
STR = [PC|MAR|IR|IRO|RCI,   RMO|GR|IDI,     DSC,            GRO|MAR|FLOD,   RO|RMI|GR|IID,      SCR,            0,      0, 0, 0, 0, 0, 0, 0]  # Store
MOV = [PC|MAR|IR,           RMO|RCI,        BRO|RI,         SCR,            0,                  0,              0,      0, 0, 0, 0, 0, 0, 0]  # Move Register to Register
CMR = [IRO|RCI,             CRM,            SCR,            0,              0,                  0,              0,      0, 0, 0, 0, 0, 0, 0]  # In/Decrement Register
REG = [IRO|RCI|EII,         EO|RI,          SCR,            0,              0,                  0,              0,      0, 0, 0, 0, 0, 0, 0]  # Register Logic
ALU = [PC|MAR|IR|IRO|EII,   RMO|RCI,        EO|RI,          SCR,            0,                  0,              0,      0, 0, 0, 0, 0, 0, 0]  # Perform ALU Operations
CFG = [IRO|FSI,             CF,             SCR,            0,              0,                  0,              0,      0, 0, 0, 0, 0, 0, 0]  # Clear Flags
SFG = [IRO|FSI,             SF,             SCR,            0,              0,                  0,              0,      0, 0, 0, 0, 0, 0, 0]  # Set Flags
JMP = [MAR|IR,              RMO|GR|IDI,     DSC,            GRO|PC|FLOD,    SCR,                0,              0,      0, 0, 0, 0, 0, 0, 0]  # Jump
HALT= [HLT,                 0,              0,              0,              0,                  0,              0,      0, 0, 0, 0, 0, 0, 0]  # Halt
LDR = [PC|MAR|IR|IRO|RCI,   RMO|GR|IDI,     DSC,            GRO|MAR|FLOD,   BRO|MAR|ADR|IN8,    RMO|RI|GR|IID,  SCR,    0, 0, 0, 0, 0, 0, 0]  # Load Address Indexed with Register



# Register new Instructions
newInst(0x00, 0xFF, NOP)  # Set base of instructions to NOP  --  When any instruction space isn't specified it will default to a NOP instruction
newInst(0x00, 0x03, LDI)
newInst(0x04, 0x07, LOD)
newInst(0x08, 0x0B, STR)
newInst(0x0C, 0x0F, MOV)
newInst(0x10, 0x1F, CMR)
newInst(0x20, 0x3F, REG)
newInst(0x40, 0x4F, ALU)
newInst(0x80, 0x8F, JMP)
newInst(0xA0, 0xAF, LDR)
newInst(0xFF, 0xFF, HALT)








eeproms = int((wordLength + (8-wordLength%8))/8)
currentEEPROM = 1
differentFiles = []
while currentEEPROM <= eeproms:

    #  ======================  Program  Files  ======================  #
    data = bytearray()
    for instruction in instructions:
        for step in instruction:
            step = step ^ activeLow  # XORS the Step with the Active Low control lines
            step = (step >> ((currentEEPROM-1)*8)) & 0xFF  # Takes the 8 bits for the current EEPROM
            data.append(step)

    #  ======================   Write  Files   ======================  #
    data = bytes(data)
    oldFile = None
    with open(str(fileName + str(currentEEPROM)), "rb") as f:
        oldFile = f.read()
    if not (data == oldFile):
        differentFiles.append(currentEEPROM)
        with open(str(fileName + str(currentEEPROM)), "wb") as f:
            f.write(data)

    currentEEPROM+=1


if len(differentFiles) == 0:
    print("NO files changed")
elif len(differentFiles) == eeproms:
    print("ALL files changed")
else:
    for changedFile in differentFiles:
        print((baseFileName + str(changedFile)) + " Changed")

print(str(uniqueInstructions) + " Unique Instructions")
print(str(instructionCount) + " Total Instructions")
print(str(eeproms) + " EEPROMs Required")