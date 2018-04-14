codes = {"halt" : "00", "loadi" : "01", "add" : "02", "push" : "03", "pop" : "04", "cmp" : "05", "jmpeq" : "06", "sub" : "07", "memr" : "08", "memw" : "09"}
regs = {"r0" : "0", "r1" : "1", "r2" : "2", "r3" : "3"}

with open("needasm.txt", "r") as f:
    content = f.readlines();
codeStr = ""
for i in content:
    i =i.split()
    print i
    if i[0] in codes:
        print i[0]
        codeStr += codes[i[0]]
        
    else:
        print "CODE NOT FOUND"
        print i[0]
        continue
    if i[1] in regs:
        r0 = True
        codeStr += regs[i[1]]
        
    elif i[1][0] == "#":
        codeStr += "000" + "0"*(3 - len(format(int(i[1][1:]), 'x'))) + format(int(i[1][1:]), 'x')
        continue   
    else:
        print "REGISTER OR LITERAL NOT FOUND"
        continue
    
    if len(i) == 2:
        if "#" not in codeStr:
            codeStr += "000"
        if r0:
            codeStr += "00"
        print codeStr
        continue
    
    if i[2] in regs:
        codeStr += regs[i[2]]
        
    elif i[2][0] == "#":
        print i[2][1:]
        codeStr += "00" + "0"*(3 - len(format(int(i[2][1:]), 'x'))) + format(int(i[2][1:]), 'x')
        print codeStr
        continue
    
    else:
        print "REGISTER OR LITERAL NOT FOUND"
        print i[2]
        continue
    
    if len(i) == 3:
        if "#" not in codeStr:
            codeStr += "0000"
        continue
    
    if i[3] in regs:
        codeStr += regs[i[3]]
        
    elif i[3][0] == "#":
        codeStr += "0"*(3 - format(int(i[3][1:]), 'x')) + format(int(i[3][1:]), 'x')
        
    else:
        print "REGISTER OR LITERAL NOT FOUND"
        continue

    if "#" not in codeStr:
        codeStr += "000"

with open("code.txt", "w") as s:
    s.write(codeStr)
               
s.close()


