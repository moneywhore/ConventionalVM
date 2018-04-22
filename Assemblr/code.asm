pushl 3
pushl 3
nop
nop
nop
nop
pop r0
pop r1
cmp r0 r1
jmpeq 16
pushl 7
pushl 12
pop r0
pop r1
add r2 r0 r1
push r2
loadi r0 26
call r0
pushl 5
pushl 3
pop r0
pop r1
add r2 r0 r1
push r2
dbg
halt
pushl 3
pop r0
pop r1
mul r2 r0 r1
push r2
ret