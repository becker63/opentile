from dataclasses import dataclass
import random

screeny = 1080
screenx = 1920

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
    curx = screeny - (o * i)
    cury = 
    i = i + 1


