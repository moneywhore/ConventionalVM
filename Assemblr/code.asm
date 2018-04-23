int 1
push r0
loadi r1 13
cmp r0 r1
jmpeq 6
jmp 0
loadi r2 0
loadi r1 6
sdec 6
rcur r0
sinc 1
int 0
loadi r3 1
sub r1 r1 r3
cmp r1 r2
jmpeq 17
jmp 9
dbg
halt