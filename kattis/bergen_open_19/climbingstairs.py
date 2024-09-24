n, r, k = (int(d) for d in input().split())

if r <= k:
    if k + k - r >= n:
        print(k*2)
        exit(0)
elif r > k:
    if r >= n:
        print(r*2)
        exit(0)

if r % 2 == n % 2:
    print(n + r)
else:
    print(n + 1 + r)
    
