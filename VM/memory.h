#ifndef MEMORY_H_
#define MEMORY_H_

#define MEM_SIZE 32768

extern unsigned int memory[MEM_SIZE];
int sp;
int sb;


typedef struct node_s {
	struct node_s *Previous;
	int returnAddress;
} Node;


Node *removeNode(Node *tail);
Node *addNode(Node* tail, int address);

char *load_file(char *filename);

int load_mem(char *filename);

#endif