w = input()
count = dict()

for c in w:
    count[c] = count.get(c, 0) + 1

rem = 0
found1 = False
for c, d in count.items():
    if d == 1:
        if found1:
            rem += 1
        else:
            found1 = True
        continue
    if d % 2 != 0:
        rem += 1
        
print(rem)