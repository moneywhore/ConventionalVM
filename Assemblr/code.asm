pushl 0
nop
int 1
push r0
loadi r1 13
cmp r0 r1
jmpeq 10
jmp 2
pushl 0
nop
loadi r1 0
nop
sdec 1
rcur r0
cmp r0 r1
jmpeq 18
jmp 12
nop
nop
sinc 1
rcur r0
cmp r0 r1
jmpeq 26
int 0
jmp 19
nop
dbg
halt