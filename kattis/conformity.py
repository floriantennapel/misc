from sys import stdin

input()

counter = dict()

for line in stdin:
    cs = sorted([int(d) for d in line.split()])
    cs = tuple(cs)

    counter[cs] = counter.get(cs, 0) + 1

hi = max(counter.values())
print(sum(c for c in counter.values() if c == hi))
