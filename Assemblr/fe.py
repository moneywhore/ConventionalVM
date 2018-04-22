import os

with open("prog.fe") as f:
    contents = f.readlines()

code = []
label_dict = {}
operators = {"+" : "pop r0\npop r1\nadd r2 r0 r1\npush r2",
             "-" : "pop r0\npop r1\nsub r2 r0 r1\npush r2",
             "*" : "pop r0\npop r1\nmul r2 r0 r1\npush r2",
             "/" : "pop r0\npop r1\ndiv r2 r0 r1\npush r2"}

def whatIsIt(line):
    if line.startswith(":"):
        return "LABEL " + line[1:]
    
    if line.startswith(";"):
        return "ret"
    
    elif line.startswith("@"):
        return "loadi r0 " + line[1:] + "\ncall r0"

    elif line in operators.keys():
        return operators[line]

    elif line.startswith("="):
        return "pop r0\npop r1\ncmp r0 r1\njmpeq " + line[1:]
    
    elif line.startswith("#"):
        line = line[1:].strip()
        line = line.replace(";", "\n")
        return line
    elif line == "!!":
        return "halt"
    else:
        return "pushl " + line

def variable_pass(lines):
    new_lines = []
    line_counter = 0
    for i in lines:
        if "LABEL" in i:
            label_dict[i.split()[1]] = str(line_counter)
            i = i.replace(i.split()[1], "nop")
            continue
        for x in i.split():
            if x in label_dict.keys():
                i = i.replace(x, label_dict[x])
            else:
                continue
            
        new_lines.append(i)
        
        line_counter += 1
    return new_lines
line_counter = 0
for i in contents:
    i = i.strip()
    code.extend(whatIsIt(i).split("\n"))
    line_counter += 1

print "\n".join(variable_pass(variable_pass(code)))

with open("code.asm", "w") as g:
    g.write("\n".join(variable_pass(variable_pass(code))))

os.system('"C://Program Files//Java//jre1.8.0_151//bin//java" -jar Assemblr.jar')
    
