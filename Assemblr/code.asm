pushl 7
loadi r0 6
call r0
nop
nop
halt
pushl 3
pop r0
pop r1
mul r2 r0 r1
push r2
pop r0
dbg
ret