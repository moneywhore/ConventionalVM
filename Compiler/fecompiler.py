with open("prog.fe") as f:
    contents = f.readlines()

code = ""

dataTypes = ["int"]

contents = [x.split() for x in contents]

variables = [i for i in contents if i[0] in dataTypes]
varNames = {}
varCount = 0
for i in variables:
    varNames[i[1]] = "$" + str(varCount)
    varCount += 1
for i in range(len(contents)):
    if contents[i][0] in dataTypes:
        contents[i] = contents[i][1:]
    for x in range(len(contents[i])):
        if contents[i][x] in varNames:
            contents[i][x] = varNames[contents[i][x]]
stack = 0
for i in contents:
    if (len(i) == 3):
        for x in i:
            if x.startswith("$"):
                if int(x[1:]) == stack:
                    code += "loadi r0 " + i[2] + "\nwcur r0\n"
                if int(x[1:]) < stack:
                    code += "sdec " + str(stack - int(x[1:])) + "\nloadi r0 " + i[2] + "\nwcur r0\n"
                if int(x[1:]) > stack:
                    code += "sinc " + str(int(x[1:]) - stack) + "\nloadi r0 " + i[2] + "\nwcur r0\n"
                stack = int(x[1:])
    if (len(i) == 1):
        for x in i:
            if x.startswith("$"):
                if int(x[1:]) == stack:
                    code += "loadi r0 " + str(0) + "\nwcur r0\n"
                if int(x[1:]) < stack:
                    code += "sdec " + str(stack - int(x[1:])) + "\nloadi r0 " + str(0) + "\nwcur r0\n"
                if int(x[1:]) > stack:
                    code += "sinc " + str(int(x[1:]) - stack) + "\nloadi r0 " + str(0) + "\nwcur r0\n" 
                
                stack = int(x[1:])      
print code            
print contents
print varNames

