from dataclasses import dataclass
import random
from turtle import window_width

x = 1080
y = 1920

@dataclass
class Window:
    sizex: int = random.randint(1, x)
    sizey: int = random.randint(1, y)
    posx: int = random.randint(1, x)
    posy: int = random.randint(1, y)

numwindows = 4
windows 
for x in range(numwindows):
    


o = x / 3

i = 1
while(i != windows):
    #print(o * i)
    i = i + 1

