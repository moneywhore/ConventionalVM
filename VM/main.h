#ifndef MAIN_H_
#define MAIN_H_
#define NUM_REGS 16
signed int regs[NUM_REGS];
Node *callInstr(int address, Node *returnStack);
Node *retInstr(Node *returnStack);
int pc;
int running;

int instrNum;
int reg1;
int reg2;
int reg3;
int imm;
int cf;

void setInstructionsInClock();

#endif
