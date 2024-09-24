n = int(input().split()[1]) 
a = [int(d) for d in input().split()]
a.sort()

if len(a) <= n:
    print(a[-1])
    exit()

scouts = [0 for _ in range(n)]
for i in range(n):
    scouts[i] = a.pop() 

for i in range(n-1, -1, -1):
    if len(a) == 0:
        break
    scouts[i] += a.pop()

print(max(scouts))


