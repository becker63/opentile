from dataclasses import dataclass
import random

x = 1080
y = 1920

@dataclass
class Point:
    sizex: int
    sizey: int
    posx: int = random.randint(1, y)
    posy: int = random.randint(1, y)


windows = 4
o = x / 3

i = 1
while(i != windows):
    print(o * i)
    i = i + 1

