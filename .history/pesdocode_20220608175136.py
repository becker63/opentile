from dataclasses import dataclass
import random

x = 1080
y = 1920

@dataclass
class Point:
    sizex: int
    sizey: int
    posx: int = 0.0
    posy: int = random.randint(1, 100)


windows = 4
o = x / 3

i = 1
while(i != windows):
    print(o * i)
    i = i + 1

