#define NUM_REGS 16
#define byte char
#include "memory.h"
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
	if (sp + 1 > 8192) {
		printf("Nothing to pop, continuing\n");
		return;
	}
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
void call(int reg1) {
	printf("call r%d\n", reg1);
	callInstr(regs[reg1], returnStack);
	return;
}
void ret() {
	printf("ret\n");
	if (returnStack->Previous == NULL) {
		printf("You have no one to return to :(\n");
		return;
	}
	retInstr(returnStack);
	return;
}
void div(int reg1, int reg2, int reg3) {
	printf("div r%d r%d r%d\n", reg1, reg2, reg3);
	regs[reg1] = regs[reg2] / regs[reg3];
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
	printf("INTERRUPT %d", imm);
	return;
}