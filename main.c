#include <stdio.h>
#include <malloc.h>

#define NUM_REGS 4
#define byte char
unsigned int regs[NUM_REGS];

unsigned int memory[8192];

int pc = 0;

int instrNum = 0;
int reg1 = 0;
int reg2 = 0;
int reg3 = 0;
int imm = 0;
int sp = 8192;
int sb = 8192;

char *load_file(char *filename) {
	FILE *codeF;
	char *buff = malloc(sizeof(char) * 1024);

	codeF = fopen(filename, "r");
	if (codeF == NULL) {
		printf("Error file not found!");
		return NULL;
	}

	fscanf(codeF, "%s", buff);
	return buff;
}


int load_mem(char *filename) {
	printf("%s\n", filename);
	char *buff = load_file(filename);

	int opcode;
	int setOpCode;
	int memoryLocation = 0;
	int inst;
	byte instNum[4];

	/*
	Loop through the hex on a single line of a text file and convert it to the opcodes/instructions.
	instNum is 4 bytes which is used to make up each opcode/instruction.
	*/
	for (opcode = 0; opcode < 1024; opcode += 4) {
		for (setOpCode = 0; setOpCode < 4; setOpCode++) {
			//Loop through the 4 bytes in the opcode int and set them to the value that it should be.
			instNum[setOpCode] = buff[opcode + setOpCode];
		}

		//Conver the character array to an int and from hex to int then set the value at the memory location to that.
		inst = (int)strtol(instNum, NULL, 16);
		memory[memoryLocation] = inst;
		memoryLocation++;
	}

	free(buff);
	return 0;
}

int fetch()
{
	return memory[pc++];
}



void decode(int instr)
{
	instrNum = (instr & 0xF000) >> 12;
	reg1 = (instr & 0xF00) >> 8;
	reg2 = (instr & 0xF0) >> 4;
	reg3 = (instr & 0xF);
	imm = (instr & 0xFF);
}

int running = 1;

void eval()
{
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
		sp--;
		memory[sp] = regs[reg1];
		printf("%d\n", sp);
		break;
	case 4:
		printf("pop r%d\n", reg1);
		regs[reg1] = memory[sp];
		memory[sp] = 0;
		sp++;
		printf("%d\n", sp);
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
		printf("%04X ", regs[i]);
	}
	printf("\nstack: ");
	for (x = 1; x<10; x++)
	{
		printf("%04X ", memory[sb - x]);
	}
	printf("\n");
}

void run()
{
	while (running)
	{
		showRegs();
		int instr = fetch();
		decode(instr);
		eval();
	}
	showRegs();
}

int main(int argc, char * argv[])
{
	if (argc < 2) {
		printf("Error! Useage %s FILENAME.", argv[0]);
		return -1;
	}

	load_mem(argv[1]);
	run();
	return 0;
}