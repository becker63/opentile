from dataclasses import dataclass
import random

screenx = 1080
screeny = 1920

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
    windows.append(Window(random.randint(1, screeny), random.randint(1, screenx),random.randint(1, screeny), random.randint(1, screenx)))
    
    
    
i = 1
o = screeny / numwindows
while(i != numwindows):
    print(o * i)
    i = i + 1


