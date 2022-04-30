#import pyperclip


#  Takes Microcode Word and creates the code chunk needed


#  HLT DSC EX AM PL E
""" ^^^ Results in vvv
wordLength = 6


HLT  = 0b100000
DSC  = 0b010000
EX   = 0b001000
AM   = 0b000100
PL   = 0b000010
E    = 0b000001
"""

lengthOfControlName = 5

print("\n\n\n\n\n")
controlLines = input("Please Paste Control Lines: ").split()
wordLength = len(controlLines)
formatString = "#0" + str(wordLength+2) + "b"

controlLineCode = "wordLength = " + str(wordLength) + "\n\n"

for n in range(wordLength):
    control = controlLines[n]
    while len(control) < 5:
        control = control + ' '
    
    lineCode = control + "= " + format(2 ** (wordLength-1-n), formatString)
    if ((wordLength-n) % 8) == 0:
        controlLineCode += '\n'
    
    controlLineCode += '\n' + lineCode

#pyperclip.copy(controlLineCode)
print(controlLineCode)
print("Code coppied to clipboard")