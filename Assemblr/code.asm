pushl 7
pushl 3
pop r0
pop r1
add r2 r0 r1
push r2
pushl 10
pop r0
pop r1
cmp r0 r1
jmpeq 17
pushl 12
pushl 7
pop r0
pop r1
add r2 r0 r1
push r2
pushl 5
pushl 6
pop r0
pop r1
sub r2 r0 r1
push r2
pop r0
dbg
halt