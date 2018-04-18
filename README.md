# ConventionalVM
VM written in C and Kotlin. It is relatively conventional, though unique at the same time.

![Old Computer](https://upload.wikimedia.org/wikipedia/commons/thumb/1/1a/Tatung-einstein-computer.png/271px-Tatung-einstein-computer.png)

## Current Supported Instructions:
  - HALT - Represented by opcode 0, stops execution, essentially acts as a failsafe if the program goes haywire
  - LOADI - Loads a register with a literal value
  - ADD - (result register) (operand register1) (operand register2) Adds two registers together and stores the value in another
  - PUSH - Pushes a register onto the stack
  - POP - Pops the top value from the stack into a register
  - CMP - Compares two registers, set the compare flag equal if they are indeed equal
  - JMP - Unconditional jump, this instruction will jump no matter what
  - JMPEQ - Conditional jump, this instruction will only jump if the compare flag is set
  - SUB - (result register) (operand register1) (operand register2) Subtracts two registers and stores the value in another
  - MEMR - (value register) (address register) Reads memory and stores the value in a register
  - MEMW - (value register) (address register) Writes a value to an address in memory
  - JMP - Jumps to a literal address
  - NOP - No operation, does nothing at all, but the program counter still counts upward
  - MUL - (result register) (operand register1) (operand register2) Multiplies two registers together and stores the value in another
  - CALL - Calls a piece of code from an address stored in the provided register
  - RET - Returns execution to the caller
  - DIV - (result register) (operand register1) (operand register2) Divides a number by another and stores the value in another
  - DBG - Prints the value of all 16 registers, and 10 lines of stack
  - LOADA - Loads the lower half of a register with a literal value
  - LOADB - Loads the upper half of a register with a literal value
  - INT - Interrupts execution using the literal as the code
 
## The VM currently has sixteen directly-editable registers:
  - r0
  - r1
  - r2
  - r3
  - r4
  - r5
  - r6
  - r7
  - r8
  - r9
  - r10
  - r11
  - r12
  - r13
  - r14
  - r15
  - program counter (uneditable)
  - stack pointer (uneditable)
  - stack base (uneditable)
  - compare flag (uneditable)

## 32-bit Instructions
  - 8 Opcode bits
  - 4 register1 bits
  - 4 register2 bits
  - 4/0 register3 bits
  - 12/16 immediate value bits
  There will never be a case where both a 16 bit immediate value and a third register will be needed, so their sizes are variable based   on case.
  
## NOTES:
The VM now supports devices that read the programs output. Right now, a "monitor" is included that makes a fancy tkinter screen for output. Will add graphics soon!

Assemblr.jar assembles any file named "code.asm" into "code.txt".

main.exe requires an input text file (like code.txt) to function.

There are some admittedly-scattered examples of assembly in the source, so if you come across this you could maybe even try to build programs for the VM!


