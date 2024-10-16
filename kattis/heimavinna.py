line = input().strip().split(';')
count = 0

for s in line:
    if '-' in s:
        a, b = (int(d) for d in s.split('-'))
        count += b - a + 1
    else:
        count += 1

print(count)
