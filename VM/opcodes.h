#ifndef OPCODES_H_
#define OPCODES_H_

void halt();
void loadi(int reg1, int imm);
void add(int reg1, int reg2, int reg3);
void push(int reg1);
void pop(int reg1);
void cmp(int reg1, int reg2);
void jmpeq(int imm);
void sub(int reg1, int reg2, int reg3);
void memr(int reg1, int reg2);
void memw(int reg1, int reg2);
void jmp(int imm);
void nop();
void mul(int reg1, int reg2, int reg3);
void call(int reg1);
void ret();
void div(int reg1, int reg2, int reg3);
void dgb();
void loada(int reg1, int imm);
void loadb(int reg1, int imm);
void interrupt(int imm);
void pushl(int imm);

#endif