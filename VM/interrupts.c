#define NUM_REGS 16
#define byte char
#include "memory.h"
#include <stdio.h>
#include "main.h"

int addressOfInterruptHandler = 0;
int lengthOfInterruptTimer = 0;

Node *interruptReturnStack;


Node *iretInstr(Node *returnStack) {
	pc = returnStack->returnAddress;
	returnStack = removeNode(returnStack);
	return returnStack;
}

void interuptINIT(){
	interruptReturnStack = (Node *) malloc(sizeof(Node));
	interruptReturnStack->Previous = NULL;
	interruptReturnStack->returnAddress = 0;
}

void iretExec(){
	iretInstr(interruptReturnStack);
	setInstructionsInClock(lengthOfInterruptTimer);
}

void BIOS(int opcodeNumber){
	switch (opcodeNumber) 
	{
	case 0:
		printf("MON:%c\n", regs[0]);
		break;
	case 1:
		regs[0] = getch();
		break;
	
	default:
		printf("Error! %d is not an implimented opcode!\n",opcodeNumber);
	break;
	}
}

void Hardware(int opcodeNumber){
	switch(opcodeNumber){
	case 16:
		//This sets the real time clock timer. 0 is auto triggered
		lengthOfInterruptTimer = regs[0]; 
		setInstructionsInClock(lengthOfInterruptTimer);
		//Register where the interrupt handler for the real time clock should go.
		addressOfInterruptHandler = regs[1];
	break;	
	case 17:
		//Setup the interrupt return stack for our command. So that when an iret is executed. We return to the pc +1
		interruptReturnStack =  addNode(interruptReturnStack,pc);
		//After the programmed cycles for the clock. Go to this address. Used to handle task schedualing.
		pc = addressOfInterruptHandler;
	break;
	}
}

void UserDefinedSoftwareInterrupts(int opcodeNumber){

}

void handleInterrupt(int code) {
	if(code >= 0 && code <= 15){
		BIOS(code);
	}else if (code >= 16 && code <= 32){
		Hardware(code);
	}else if (code >= 33 && code <= 255){
		UserDefinedSoftwareInterrupts(code);
	}else{
		printf("Error not a valid opcode. Opcode range is 0-255. Refer to manual for more information\n");
	}
}

