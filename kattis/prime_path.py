from queue import Queue
from math import sqrt
from sys import stdin

def all_primes():
    nums = [True for _ in range(10000)]
    nums[0] = False
    nums[1] = False
    for i in range(int(sqrt(10000))+1):
        if not nums[i]:
            continue
        for j in range(2*i, 10000, i):
            nums[j] = False
    return set(i for i, n in enumerate(nums) if n)

primes = all_primes()


def get_neighbors(prime):
    neighbors = []
    for i, p in enumerate(str(prime)):
        for j in range(1 if i == 0 else 0, 10):
            if j == int(p):
                continue
            neighbor = [c for c in str(prime)]
            neighbor[i] = str(j)
            neighbor = int(''.join(neighbor)) 
            if (neighbor in primes):
                neighbors.append(neighbor)
    return neighbors

def path_cost(p1, p2):
    next = Queue()
    visited = set()

    next.put((p1, 0))

    while (not next.empty()):
        current, path = next.get()
        if current == p2:
            return path
        if current in visited:
            continue
        visited.add(current)

        for p in get_neighbors(current):
            next.put((p, path+1))

input()
for line in stdin:
    p1, p2 = (int(d) for d in line.split())
    print(path_cost(p1, p2))
        
        

