from dataclasses import dataclass
import random

screenx = 1920
screeny = 1080

#fancy c like struct
@dataclass
class Window:
    sizex: int
    sizey: int
    posx: int
    posy: int


numwindows = 3
windows = []


#generates some random windows
for i in range(numwindows):
    windows.append(Window(random.randint(1, screenx), random.randint(1, screeny),random.randint(1, screenx), random.randint(1, screeny)))
    
    
    
i = 1
o = screeny / (numwindows - 1)
while(i != numwindows):
    expx = screeny - (o * i)
    expy = screeny / 2
    
    slope = (expy - windows[i].posy) / (expx - windows[i].posx)
    
    print(f"x: {windows[i].posx}\ny: {windows[i].posy}\nexpected x: {expx}\nexpected y: {expy}\nslope: {slope}\n {expx - windows[i].posx}\n{expy - windows[i].posy}\n \n")
    
    i = i + 1


