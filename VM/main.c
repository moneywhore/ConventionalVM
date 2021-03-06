#include <stdio.h>
#include <malloc.h>
#include "memory.h"
#include "opcodes.h"

#define NUM_REGS 16
#define byte char
signed int regs[NUM_REGS];
int githubfuckingload;
int pc = 0;
int running = 1;
int instructionsInClock =  -1;

int instrNum = 0;
int reg1 = 0;
int reg2 = 0;
int reg3 = 0;
int imm = 0;
int cf = 0;

void setInstructionsInClock(int value){
	instructionsInClock = value;
}

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


Node *callInstr(int address, Node *returnStack) {
	printf("PC: %d\n",pc);
	returnStack = addNode(returnStack, pc);
	pc = address;
	printf("PC: %d\n",pc);
	return returnStack;
}

Node *retInstr(Node *returnStack) {
	pc = returnStack->returnAddress;
	returnStack = removeNode(returnStack);
	return returnStack;
}

void showRegs()
{
	int i;
	int x;
	printf("MONN:regs\n");
	for (i = 0; i<NUM_REGS; i++)
	{
		printf("NMON:%08X\n", regs[i]);
	}
	printf("\nMONN:stack: ");
	for (x = 1; x<10; x++)
	{
		printf("%04X ", memory[sb - x]);
	}
	printf("\n");
}

Node *eval(Node *returnStack)
{
	int upperHalf = 0;
	int lowerHalf = 0;
	int newVal = 0;
	switch (instrNum)
	{
	case 0:
		halt();
		break;
	case 1:
		loadi(reg1, imm);
		break;
	case 2:
		add(reg1, reg2, reg3);
		break;
	case 3:
		push(reg1);
		break;
	case 4:
		pop(reg1);
		break;
	case 5:
		cmp(reg1, reg2);
		break;
	case 6:
		jmpeq(imm);
		break;
	case 7:
		sub(reg1, reg2, reg3);
		break;
	case 8:
		memr(reg1, reg2);
		break;
	case 9:
		memw(reg1, reg2);
		break;
	case 10:
		jmp(imm);
		break;
	case 11:
		nop();
		break;
	case 12:
		mul(reg1, reg2, reg3);
		break;
	case 13:
		returnStack = call(reg1, returnStack);
		break;
	case 14:
		returnStack = ret(returnStack);
		break;
	case 15:
		div(reg1, reg2, reg3);
		break;
	case 16:
		dbg();
		break;
	case 17:
		loada(reg1, imm);
		break;
	case 18:
		loadb(reg1, imm);
		break;
	case 19:
		interrupt(imm);
		break;
	case 20:
		pushl(imm);
		break;
	case 21:
		stackInc(imm);
		break;
	case 22:
		stackDec(imm);
		break;
	case 23:
		readCur(reg1);
		break;
	case 24:
		writeCur(reg1);
		break;
	case 25:
		returnStack = calli(imm,returnStack);
		break;
	case 26:
		iret();
		break;
	}
	return returnStack;
}

void run(Node *returnStack)
{
	while (running)
	{
		//Check if the time left in the clock is greater than 0. If its less than 0. Ignore it as well. 
		//tl;dr if its equal to zero interrupt the cpu to let it know to change which task to run
		printf("clocks left till int: %d\n",instructionsInClock);
		if(instructionsInClock > 0 || instructionsInClock < 0){
			int instr = fetch();
			decode(instr);
			returnStack = eval(returnStack);
		}else{
			//Trigger Programming control clock. Refer to commit that this was added in for more information on that.
			interrupt(17);
		}
		instructionsInClock--;
		
	}
}

int main(int argc, char * argv[])
{
	if (argc < 2) {
		printf("Error: %s <FILENAME>.", argv[0]);
		return -1;
	}
	Node *n = malloc(sizeof(Node));
	n->Previous=NULL;
	n->returnAddress= (int)NULL;

	interuptINIT();

	load_mem(argv[1]);
	run(n);
	return 0;
}
