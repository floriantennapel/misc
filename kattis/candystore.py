n, q = (int(d) for d in input().split())
names = dict()

for _ in range(n):
    f, l = input().strip().split()
    key = f[0] + l[0]
    if key not in names:
        names[key] = []

    names[key].append((f, l))

for _ in range(q):
    key = input().strip()
    people = names.get(key, [])

    match len(people):
        case 0:
            print('nobody');
        case 1:
            f, l = people[0] 
            print(f, l)
        case _:
            print('ambiguous')

