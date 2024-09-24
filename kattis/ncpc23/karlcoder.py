checked = {}

prev = 0
i = 1
while True:
    print(f'buf[{i}]')
    b = int(input())
    checked[i] = b
    if b == 0:
        break
    
    prev = i
    i *= 2

if i == 1:
    print('buf[0]')
    if input() == '0':
        print('strlen(buf) = 0')
    else:
        print('strlen(buf) = 1')
    exit(0)

lo = prev
hi = i

while hi != lo:
    t = lo + (hi - lo) // 2
    if t in checked:
        b = checked[t]
    else:
        print(f'buf[{t}]')
        b = int(input())

    if b != 0:
        lo = t+1
    else:
        hi = t

print(f'strlen(buf) = {hi}')