from math import sqrt
from sys import stdin

class Shape:
    def __init__(self, shape, size):
        self.shape = shape
        self.size = size

    def __lt__(self, other):
        if self.shape == other.shape:
            return self.size < other.size
        elif self.shape == 'cylinder':
            if self.size < sqrt(2*other.size*other.size) / 2:
                if self.size * 2 <= other.size:
                    return True
                else:
                    print('impossible')
                    exit(0)
        else:
            if self.size < other.size * 2:
                if sqrt(2*self.size*self.size) / 2. <= other.size:
                    return True
                else:
                    print('impossible')
                    exit(0)

    def __str__(self):
        return f'{self.shape} {self.size}'


def read_input() -> list[Shape]:
    retlist = []

    input() #ignoring n
    for line in stdin.readlines():
        shape, a = line.split()
        retlist.append(Shape(shape, int(a)))
    return retlist


shapes = read_input()
shapes.sort()

for s in shapes:
    print(s)
