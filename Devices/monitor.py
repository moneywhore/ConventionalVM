import subprocess
from Tkinter import *

p = subprocess.Popen(['..//Out//main.exe', '..//Assemblr//code.txt'], 
                     stdout=subprocess.PIPE)

master = Tk()

w = Canvas(master, bg="black", width=1024, height=768)
row = 0
for line in iter(p.stdout.readline, ""):
    if line.startswith("MON:"):
        row += 30
        w.create_text(512,row,fill="#fff", font=(None, 11), text=line[4:])
w.pack()
master.mainloop()
