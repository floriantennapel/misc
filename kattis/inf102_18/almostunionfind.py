from sys import stdin

def join(sets, p, q):
    if sets[p][0] == q or sets[q][0] == p:
        return

    if sets[p][0] != p:
        p = sets[p][0]
    if sets[q][0] != q:
        q = sets[q][0]

    sets[q][1] += sets[p][1]
    for child in sets[p][1]:
        sets[child][0] = q
    sets[p][1] = []
    sets[p][0] = q
    sets[q][1].append(p)


def move(sets, p, q):
    if sets[p][0] == q or sets[q][0] == p:
        return
    
    if len(sets[p][1]) != 0:
        sets[sets[p][1][0]][1] += sets[p][1][1:]
        for child in sets[p][1][1:]:
            sets[child][0] = sets[p][1][0]
        sets[p][1] = []
    
    if sets[p][0] != p:
        sets[sets[p][0]][1].remove(p)

    if sets[q][0] != q:
        q = sets[q][0]

    sets[q][1].append(p)
    sets[p][0] = q


def count(sets, p):
    if sets[p][0] != p:
        p = sets[p][0]

    return (len(sets[p][1]) + 1, sum(sets[p][1]) + p)


while stdin.readable():
    try:
        n, m = (int(d) for d in input().split())
    except:
        break
    n += 1

    sets = [[i, []] for i in range(n)]
    for _ in range(m):
        line = input()
        if len(line.split()) == 3:
            t, p, q = (int(d) for d in line.split())
            if t == 1:
                join(sets, p, q)
            elif t == 2:
                move(sets, p, q)
        else:
            t, p = (int(d) for d in line.split())
            res = count(sets, p)
            print(res[0], res[1])
    
    
