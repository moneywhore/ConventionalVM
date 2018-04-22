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

    elif line.startswith("<"):
        return "INCLUDE " + (line[1:])[:-1]
    
    elif line.startswith(";"):
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

def precompile_pass(lines):
    added_code = []
    for i in lines:
        if "INCLUDE" in i:
            added_code += include_file(i.split()[1])
        else:
            added_code.append(i)
    return added_code

def include_file(name):
    additional_code = []
    with open(name) as f:
        contents = f.readlines()
    for i in contents:
        i = i.strip()
        additional_code.extend(whatIsIt(i).split("\n"))
    return additional_code

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

one_line_parsed = []
for i in contents:
    i = i.strip()
    one_line_parsed.extend(i.split(","))
for i in one_line_parsed:
    i = i.strip()
    code.extend(whatIsIt(i).split("\n"))
code = precompile_pass(code)

print code

print "\n".join(variable_pass(variable_pass(code)))

with open("code.asm", "w") as g:
    g.write("\n".join(variable_pass(variable_pass(code))))

os.system('"C://Program Files//Java//jre1.8.0_151//bin//java" -jar Assemblr.jar')
    
