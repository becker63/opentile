from dataclasses import dataclass
import random
from turtle import window_width

x = 1080
y = 1920

@dataclass
class Window:
    sizex
    sizey
    posx
    posy

numwindows = 4
windows = []


for x in range(numwindows):
    windows.append(Window())
    
for window in windows:
    print(window)


