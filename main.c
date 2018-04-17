#include <stdio.h>
#include <malloc.h>
#include "memory.c"
#include "interrupts.c"

#define NUM_REGS 16
#define byte char
signed int regs[NUM_REGS];

int pc = 0;
int running = 1;

int instrNum = 0;
int reg1 = 0;
int reg2 = 0;
int reg3 = 0;
int imm = 0;
int cf = 0;

int fetch()
{
	return memory[pc++];
}

void decode(int instr)
{
	instrNum = (instr & 0xFF000000) >> 24;
	reg1 = (instr & 0xF00000) >> 20;
	reg2 = (instr & 0xF0000) >> 16;
	reg3 = (instr & 0xF000) >> 12;
	imm = (instr & 0xFFFF);
}

void callInstr(int address, Node *returnStack){
	returnStack = addNode(returnStack,pc+1);
	pc = address;
}

void retInstr(Node *returnStack){
	pc= returnStack->returnAddress;
	returnStack = removeNode(returnStack);
}


void eval(Node *returnStack)
{
	int upperHalf = 0;
	int lowerHalf = 0;
	int newVal = 0;
	switch (instrNum)
	{
	case 0:
		printf("halt\n");
		running = 0;
		break;
	case 1:
		printf("loadi r%d #%d\n", reg1, imm);
		regs[reg1] = imm;
		break;
	case 2:
		printf("add r%d r%d r%d\n", reg1, reg2, reg3);
		regs[reg1] = regs[reg2] + regs[reg3];
		break;
	case 3:
		printf("push r%d\n", reg1);
		if (sp - 1 <= 4096) {
			printf("Wow! Looks like you've reached the limit on the stack\nSEG_FAULT\nContinuing...\n");
			break;
		}
		sp--;
		memory[sp] = regs[reg1];
		printf("%d\n", sp);
		break;
	case 4:
		printf("pop r%d\n", reg1);
		if (sp + 1 > 8192) {
			printf("Nothing to pop, continuing\n");
			break;
		}
		regs[reg1] = memory[sp];
		memory[sp] = 0;
		sp++;
		printf("%d\n", sp);
		break;
	case 5:
		printf("cmp r%d r%d\n", reg1, reg2);
		if (regs[reg1] == regs[reg2]) {
			cf = 1;
		}
		else {
			cf = 0;
		}
		break;
	case 6:
		if (cf) {
			printf("jmpeq %d\n", imm);
			pc = imm;
		}
		break;
	case 7:
		printf("sub r%d r%d r%d\n", reg1, reg2, reg3);
		regs[reg1] = regs[reg2] - regs[reg3];
		break;
	case 8:
		printf("memr r%d r%d\n", reg1, reg2);
		regs[reg1] = memory[regs[reg2]];
		break;
	case 9:
		printf("memw r%d r%d\n", reg1, reg2);
		if (regs[reg2] <= 4096) {
			printf("Hey! You can't write to program code, silly billy.\n");
			break;
		}
		memory[regs[reg2]] = regs[reg1];
		break;
	case 10:
		printf("jmp %d\n", imm);
		pc = imm;
		break;
	case 11:
		printf("nop\n");
		break;
	case 12:
		printf("mul r%d r%d r%d\n", reg1, reg2, reg3);
		regs[reg1] = regs[reg2] * regs[reg3];
		break;
	case 13:
		printf("call r%d\n", reg1);
		callInstr(regs[reg1],returnStack);
		break;
	case 14:
		printf("ret\n");
		if (returnStack->Previous == NULL) {
			printf("You have no one to return to :(\n");
			break;
		}
		retInstr(returnStack);
		break;
	case 15:
		printf("div r%d r%d r%d\n", reg1, reg2, reg3);
		regs[reg1] = regs[reg2] / regs[reg3];
		break;
	case 16:
		printf("DBG:\n");
		showRegs();
		break;
	case 17:
		printf("loada r%d, %d\n", reg1, imm);
		upperHalf = (regs[reg1] & 0xFFFF) >> 16;	
		printf("%d\n", upperHalf);
		newVal = (upperHalf * 65536) + imm;
		regs[reg1] = newVal;
		break;
	case 18:
		printf("loadb r%d, %d\n", reg1, imm);
		lowerHalf = (regs[reg1] & 0xFFFF);
		printf("%d\n", lowerHalf);
		newVal = (imm * 65536) + lowerHalf;
		regs[reg1] = newVal;
		break;
	case 19:
		printf("INTERRUPT %d", imm);
		handleInterrupt(imm);
		break;
	}
}


void showRegs()
{
	int i;
	int x;
	printf("regs = ");
	for (i = 0; i<NUM_REGS; i++)
	{
		printf("%08X ", regs[i]);
	}
	printf("\nstack: ");
	for (x = 1; x<10; x++)
	{
		printf("%04X ", memory[sb - x]);
	}
	printf("\n");
}

void run(Node *returnStack)
{
	while (running)
	{
		int instr = fetch();
		decode(instr);
		eval(returnStack);
	}
	showRegs();
}

int main(int argc, char * argv[])
{
	if (argc < 2) {
		printf("Error: %s <FILENAME>.", argv[0]);
		return -1;
	}
	Node *n = malloc(sizeof(Node));
	n->Previous=NULL;
	n->returnAddress=NULL;

	load_mem(argv[1]);
	run(n);
	return 0;
}
