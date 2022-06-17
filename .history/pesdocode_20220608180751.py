from dataclasses import dataclass
import random
from turtle import window_width

x = 1080
y = 1920

@dataclass
class Window:
    sizex: int
    sizey: int
    posx: int
    posy: int

numwindows = 4
windows = []


for x in range(numwindows):
    windows.append(Window(random.randint(1, x),
random.randint(1, y),random.randint(1, x),
random.randint(1, y)))
    
for window in windows:
    print(window)


