def components(n, k):
    used = set()
    for i in range(n-1, 0, -1):
        if i <= k:
            used.add(i)
            k -= i
    
    return sorted(list(used))

n, k = (int(d) for d in input().split())
comps = set(components(n, k))

pages = [-1 for _ in range(n)]

hi = n
for i in range(n):
    if i+1 in comps:
        pages[i] = hi
        hi -= 1

lo = 1
for i, page in enumerate(pages):
    if page == -1:
        pages[i] = lo
        lo += 1

for p in pages:
    print(p, end=' ')
