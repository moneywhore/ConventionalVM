import subprocess
from Tkinter import *

p = subprocess.Popen(['..//Out//main.exe', '..//Assemblr//code.txt'], 
                     stdout=subprocess.PIPE)

master = Tk()

w = Canvas(master, bg="black", width=1024, height=768)
row = 100
for line in iter(p.stdout.readline, ""):
    if line.startswith("MON:"):
        w.create_text(512,row, fill="#fff", text=line[4:])
        row +=30
w.pack()
master.mainloop()
