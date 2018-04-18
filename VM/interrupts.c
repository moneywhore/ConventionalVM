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
	}
}