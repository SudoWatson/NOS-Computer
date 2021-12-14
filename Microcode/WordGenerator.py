import pyperclip


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

pyperclip.copy(controlLineCode)
print("Code coppied to clipboard")