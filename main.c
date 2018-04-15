#include <stdio.h>
#include <malloc.h>

typedef struct node_s{
    struct node_s *Previous;
    int returnAddress;
} Node;

Node *removeNode(Node *tail){
    Node *previous =  tail->Previous;
    free(tail);
    return previous;
}

Node *addNode(Node* tail,int address){
    Node *n = malloc(sizeof(Node));
    n->Previous =tail;
    n->returnAddress=address;
    return n;
}

#define NUM_REGS 4
#define byte char
signed int regs[NUM_REGS];

unsigned int memory[32768];

int pc = 0;
int running = 1;

int instrNum = 0;
int reg1 = 0;
int reg2 = 0;
int reg3 = 0;
int imm = 0;
int sp = 32768;
int sb = 32768;
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
		showRegs();
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
