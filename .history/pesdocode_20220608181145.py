from dataclasses import dataclass
import random
from turtle import window_width

screenx = 1080
screeny = 1920

@dataclass
class Window:
    sizex: int
    sizey: int
    posx: int
    posy: int

numwindows = 4
windows = []


#generates some random windows
for i in range(numwindows):
    windows.append(Window(random.randint(1, screeny), random.randint(1, screenx),random.randint(1, screeny), random.randint(1, screenx)))
    
for window in windows:
    print(window)


