#include <stdio.h>
#include <malloc.h>

#define NUM_REGS 4
#define byte char

signed int regs[NUM_REGS];

unsigned int memory[8192];

int pc = 0;

int instrNum = 0;
int reg1 = 0;
int reg2 = 0;
int reg3 = 0;
int imm = 0;
int sp = 8192;
int sb = 8192;
int cf = 0;

char *load_file(char *filename) {
	FILE *codeF;
	char *buff = malloc(sizeof(char) * 2048);

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
	byte instNum[8];

	/*
	Loop through the hex on a single line of a text file and convert it to the opcodes/instructions.
	instNum is 8 bytes which is used to make up each opcode/instruction.
	*/
	for (opcode = 0; opcode < 1024; opcode += 8) {
		for (setOpCode = 0; setOpCode < 8; setOpCode++) {
			//Loop through the 8 bytes in the opcode int and set them to the value that it should be.
			instNum[setOpCode] = buff[opcode + setOpCode];
		}

		//Convert the character array to an int and from hex to int then set the value at the memory location to that.
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
	instrNum = (instr & 0xFF000000) >> 24;
	reg1 = (instr & 0xF00000) >> 20;
	reg2 = (instr & 0xF0000) >> 16;
	reg3 = (instr & 0xF000) >> 12;
	imm = (instr & 0xFFFF);
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
<<<<<<< HEAD
		if (cf) {
			printf("jmpeq %d\n", imm);
=======
		printf("jmpeq %d\n", imm);
		if(cf) {
>>>>>>> 080b34fdf0ca95e928792c31e82c7705d3ef44d9
			pc = imm;
		}else
		{
			printf("Didn't jump\n");
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
<<<<<<< HEAD
		printf("memw r%d r%d\n", reg1, reg2);
		memory[regs[reg2]] = regs[reg1];
		break;
	case 10:
		printf("jmp %d\n", imm);
		pc = imm;
	}
	case 11:
		printf("nop");
=======
	  printf("memw r%d r%d\n", reg1, reg2);
	  printf("Before set. Address %d, Value: %d\n", regs[reg2], memory[regs[reg2]]);
      memory[regs[reg2]] = regs[reg1];
	  printf("Address %d, Value: %d\n",regs[reg2], memory[regs[reg2]]);
	  break;
>>>>>>> 080b34fdf0ca95e928792c31e82c7705d3ef44d9
	}
}

void showRegs()
{
	int i;
	int x;
	printf("regs = ");
	for (i = 0; i<NUM_REGS; i++)
	{
		printf("Reg %d: %08X ",i, regs[i]);
	}
	printf("cf: %d pc: %d", cf,pc);
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
