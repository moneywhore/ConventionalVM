#ifndef MAIN_H_
#define MAIN_H_
#define NUM_REGS 16
signed int regs[NUM_REGS];
void callInstr(int address, Node *returnStack);
void retInstr(Node *returnStack);
Node *returnStack;
int pc;
int running;

int instrNum;
int reg1;
int reg2;
int reg3;
int imm;
int cf;

#endif
