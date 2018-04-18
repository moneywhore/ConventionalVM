#define NUM_REGS 16
#define byte char
#include "memory.h"
#include <stdio.h>
#include "main.h"
void handleInterrupt(int code) {
	switch (code) 
	{
	case 0:
		printf("MON:%c\n", regs[0]);
		return;
	case 1:
		regs[0] = getch();
		return;
	case 2:
		printf("MON:");
		for (int i=1;i<regs[1];i++) {
			int first = (memory[regs[0] - i] & 0xFF00) >> 8;
			int second = (memory[regs[0] - i] & 0x00FF);
			printf("%c", first);
			printf("%c", second);
		}
		printf("\n");
		printf("MON: \n");
		return;
	}
}