n = int(input())

days = [0 for _ in range(366)]

for _ in range(n):
    s, t = (int(d) for d in input().split(' '))
    for i in range(s, t+1):
        days[i] = 1
        
print(sum(days))