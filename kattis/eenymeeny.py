rhyme = len(input().split(' '))
n = int(input())
names = []

for _ in range(n):
    names.append(input().strip())

i = 0
g = 0
groups = [[], []]
while len(names) > 1:
    i = (i + rhyme - 1) % len(names)
    groups[g].append(names.pop(i))
    g = (g + 1) % 2

groups[g].append(names[0])

for group in groups:
    print(len(group))
    for name in group:
        print(name)

