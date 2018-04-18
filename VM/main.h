#ifndef MAIN_H_
#define MAIN_H_

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
