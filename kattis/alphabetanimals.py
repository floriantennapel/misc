prev = input().strip()
n = int(input())
animals = dict()

first_c = prev[-1]

for _ in range(n):
    a = input().strip()
    if a[0] in animals:
        animals[a[0]].append(a)
    else:
        animals[a[0]] = [a]

if first_c not in animals:
    print('?')
    exit(0)

for a in animals[first_c]:
    if a[-1] not in animals or len(animals[a[-1]]) == 1 and animals[a[-1]][0] == a:
        print(a+'!')
        exit(0)

print(animals[first_c][0])



