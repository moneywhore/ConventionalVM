#include <stdio.h>

#define NUM_REGS 4
unsigned regs[ NUM_REGS ];

unsigned memory[8192];

int pc = 0;

void load_mem(const char *filename[]) {
	printf("%s\n", filename[1]);
	FILE *codeF;
	char buff[1024];
	codeF = fopen(filename[1], "r");
	fscanf(codeF, "%s", buff);
	int i;
	int x;
	int h = 0;
	int inst;
	char instNum[4];
	for (i =0;i < 1024;i+=4) {
		for (x=0;x < 4; x++) {
			instNum[x] = buff[i+x];
		}
		inst = (int)strtol(instNum, NULL, 16);
		memory[h] = inst;
		h++;
		
	}
}

int fetch()
{
  return memory[ pc++ ];
}

int instrNum = 0;
int reg1     = 0;
int reg2     = 0;
int reg3     = 0;
int imm      = 0;
int sp = 8192;
int sb = 8192;

void decode( int instr )
{
  instrNum = (instr & 0xF000) >> 12;
  reg1     = (instr & 0xF00 ) >>  8;
  reg2     = (instr & 0xF0  ) >>  4;
  reg3     = (instr & 0xF   );
  imm      = (instr & 0xFF  );
}

int running = 1;

void eval()
{
  switch( instrNum )
  {
    case 0:
      printf( "halt\n" );
      running = 0;
      break;
    case 1:
      printf( "loadi r%d #%d\n", reg1, imm );
      regs[ reg1 ] = imm;
      break;
    case 2:
      printf( "add r%d r%d r%d\n", reg1, reg2, reg3 );
      regs[ reg1 ] = regs[ reg2 ] + regs[ reg3 ];
      break;
	case 3:
	  printf( "push r%d\n", reg1);
      sp--;
	  memory[ sp ] = regs[ reg1 ];
	  printf( "%d\n", sp);
	  break;
	case 4:
	  printf( "pop r%d\n", reg1);
	  regs[ reg1 ] = memory[ sp ];
	  memory[ sp ] = 0;
	  sp++;
	  printf( "%d\n", sp);
	  break;
  }
}

void showRegs()
{
  int i;
  int x;
  printf( "regs = " );
  for( i=0; i<NUM_REGS; i++ )
    printf( "%04X ", regs[ i ] );

  printf( "\nstack: " );
  for ( x=1; x<10; x++ ) {
	printf("%04X ", memory[sb - x]);
  }
  printf( "\n" );
}

void run()
{
  while( running )
  {
    showRegs();
    int instr = fetch();
    decode( instr );
    eval();
  }
  showRegs();
}

int main( int argc, const char * argv[] )
{
  load_mem(argv);
  run();
  return 0;
}