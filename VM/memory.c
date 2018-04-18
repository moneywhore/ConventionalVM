#include <stdio.h>
#define NUM_REGS 16
#define byte char

typedef struct node_s {
	struct node_s *Previous;
	int returnAddress;
} Node;

Node *removeNode(Node *tail) {
	Node *previous = tail->Previous;
	free(tail);
	return previous;
}

Node *addNode(Node* tail, int address) {
	Node *n = malloc(sizeof(Node));
	n->Previous = tail;
	n->returnAddress = address;
	return n;
}

unsigned int memory[32768];
int sp = 32768;
int sb = 32768;


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