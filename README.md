# ConventionalVM
VM written in C and Kotlin. It is relatively conventional, though unique at the same time

Current Supported Instructions:
  - HALT - Represented by opcode 0, stops execution, essentially acts as a failsafe if the program goes haywire
  - LOADI - Loads a register with a literal value
  - ADD - (result register) (operand register1) (operand register2) Adds two registers together and stores the value in another
  - PUSH - Pushes a register onto the stack
  - POP - Pops the top value from the stack into a register
  - CMP - Compares two registers, set the compare flag equal if they are indeed equal
  - JMP - Unconditional jump, this instruction will jump no matter what
  - JMPEQ - Conditional jump, this instruction will only jump if the compare flag is set
  - SUB - (result register) (operand register1) (operand register2) Subtracts two registers and store the value in another
  - MEMR - (value register) (address register) Reads memory and stores the value in a register
  - MEMW - (value register) (address register) Writes a value to an address in memory
  - JMP - Jumps to a literal address
  - NOP - No operation, does nothing at all, but the program counter still counts upward
  - MUL - (result register) (operand register1) (operand register2) Multiplies two registers together and stores the value in another
  - CALL - Calls a piece of code from an address stored in the provided register
  - RET - Returns execution to the caller
The VM currently has four workable registers (r0,r1,r2,r3)
The stack right now is 8 kilobytes in size, and I have a feeling we should probably change that at some point.
Instruction set is 32-bit: 8 opcode bits, 4 register1 bits, 4 register2 bits, 4/0 register3 bits, and 12/16 immediate value bits

Assemblr.jar assembles any file named "code.asm" into "code.txt"

main.exe requires an input text file (like code.txt) to function

There are some admittedly-scattered examples of assembly in the source, so if you come across this you could maybe even try to build programs for the VM!


