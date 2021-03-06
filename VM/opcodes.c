#define NUM_REGS 16
#define byte char
#include "memory.h"
#include "interrupt.h"
#include <stdio.h>
#include "main.h"

signed int regs[NUM_REGS];

int upperHalf = 0;
int lowerHalf = 0;
int newVal = 0;

void halt() {
	printf("HALT\n");
	running = 0;
	return;
}
void loadi(int reg1, int imm) {
	printf("loadi r%d #%d\n", reg1, imm);
	regs[reg1] = imm;
	return;
}
void add(int reg1, int reg2, int reg3) {
	printf("add r%d r%d r%d\n", reg1, reg2, reg3);
	regs[reg1] = regs[reg2] + regs[reg3];
	return;
}
void push(int reg1) {
	printf("push r%d\n", reg1);
	sp--;
	memory[sp] = regs[reg1];
	printf("%d\n", sp);
	return;
}

void pop(int reg1) {
	printf("pop r%d\n", reg1);
	regs[reg1] = memory[sp];
	memory[sp] = 0;
	sp++;
	printf("%d\n", sp);
	return;
}
void cmp(int reg1, int reg2) {
	printf("cmp r%d r%d\n", reg1, reg2);
	if (regs[reg1] == regs[reg2]) {
		cf = 1;
	}
	else {
		cf = 0;
	}
	return;
}
void jmpeq(int imm) {
	if (cf) {
		printf("jmpeq %d\n", imm);
		pc = imm;
	}
	return;
}
void sub(int reg1, int reg2, int reg3) {
	printf("sub r%d r%d r%d\n", reg1, reg2, reg3);
	regs[reg1] = regs[reg2] - regs[reg3];
	return;
}
void memr(int reg1, int reg2) {
	printf("memr r%d r%d\n", reg1, reg2);
	regs[reg1] = memory[regs[reg2]];
	return;
}
void memw(int reg1, int reg2) {
	printf("memw r%d r%d\n", reg1, reg2);
	memory[regs[reg2]] = regs[reg1];
	return;
}
void jmp(int imm) {
	printf("jmp %d\n", imm);
	pc = imm;
	return;
}
void nop() {
	printf("nop\n");
	return;
}
void mul(int reg1, int reg2, int reg3) {
	printf("mul r%d r%d r%d\n", reg1, reg2, reg3);
	regs[reg1] = regs[reg2] * regs[reg3];
	return;
}
Node *call(int reg1, Node *returnStack) {
	printf("call r%d\n", reg1);
	returnStack = callInstr(regs[reg1], returnStack);
	return returnStack;
}

Node *calli(int imm, Node *returnStack){
	printf("calli imm: %d\n",imm);
	returnStack = callInstr(imm,returnStack);
	return returnStack;
}


void iret(){
	printf("IRET\n");
	iretExec();
}

Node *ret(Node *returnStack) {
	printf("ret\n");
	if (returnStack->returnAddress == 0) {
		printf("You have no one to return to ;(\n");
		return returnStack;
	}
	returnStack = retInstr(returnStack);
	return returnStack;
}
void div(int reg1, int reg2, int reg3) {
	printf("div r%d r%d r%d\n", reg1, reg2, reg3);
	regs[reg1] = regs[reg2] / regs[reg3];
	return;
}
void dbg() {
	printf("MONN:DBG:\n");
	showRegs();
	return;
}
void loada(int reg1, int imm) {
	printf("loada r%d, %d\n", reg1, imm);
	upperHalf = (regs[reg1] & 0xFFFF) >> 16;
	newVal = (upperHalf * 65536) + imm;
	regs[reg1] = newVal;
	return;
}
void loadb(int reg1, int imm) {
	printf("loadb r%d, %d\n", reg1, imm);
	lowerHalf = (regs[reg1] & 0xFFFF);
	newVal = (imm * 65536) + lowerHalf;
	regs[reg1] = newVal;
	return;
}
void interrupt(int imm) {
	printf("INTERRUPT %d\n", imm);
	handleInterrupt(imm);
	return;
}
void pushl(int imm) {
	printf("pushl %d\n", imm);
	sp--;
	memory[sp] = (imm & 0x0000FFFF);
	return;
}
void stackInc(int imm) {
	printf("sinc %d\n", imm);
	sp -= imm;
	printf("%d\n", sp);
	return;
}
void stackDec(int imm) {
	printf("sdec %d\n", imm);
	sp += imm;
	printf("%d\n", sp);
	return;
}
void readCur(int reg1) {
	printf("rcur r%d\n", reg1);
	regs[reg1] = memory[sp];
	return;
}
void writeCur(int reg1) {
	printf("wcur r%d\n", reg1);
	memory[sp] = regs[reg1];
	return;
}
