loadi r0 73
call r0
halt
nop
pushl 7
push r6
pop r0
pop r1
div r2 r0 r1
push r2
pop r5
loadi r0 108
int 0
loadi r0 111
int 0
loadi r0 108
int 0
loadi r0 32
int 0
loadi r0 104
int 0
loadi r0 101
int 0
loadi r0 121
int 0
loadi r0 32
int 0
loadi r0 108
int 0
loadi r0 111
int 0
loadi r0 111
int 0
loadi r0 107
int 0
loadi r0 32
int 0
loadi r0 97
int 0
loadi r0 116
int 0
loadi r0 32
int 0
loadi r0 109
int 0
loadi r0 101
int 0
loadi r0 32
int 0
loadi r0 105
int 0
loadi r0 109
int 0
loadi r0 32
int 0
loadi r0 97
int 0
loadi r0 32
int 0
loadi r0 115
int 0
loadi r0 116
int 0
loadi r0 114
int 0
loadi r0 105
int 0
loadi r0 110
int 0
loadi r0 103
int 0
ret
nop
pushl 3
pushl 7
pop r0
pop r1
mul r2 r0 r1
push r2
pop r6
loadi r0 4
call r0
dbg
ret