from dataclasses import dataclass

@dataclass
class Point:
    sizex: float
    screeny: float
    z: float = 0.0

x = 1080
y = 1920

windows = 4
o = x / 3

i = 1
while(i != windows):
    print(o * i)
    i = i + 1

