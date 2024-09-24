from sys import stdin

r = {'I': 1, 'V': 5, 'X': 10, 'L': 50, 'C': 100, 'D': 500, 'M': 1000}

input()
for line in stdin.read().splitlines():
    sum = 0
    prev = 0
    for c in line:
        num = r[c]

        if prev < num:
            sum += num - prev
            #print(f'adding {num} - {prev}')
            prev = None
        else:
            sum += prev
            #print(f'adding {prev}')
            prev = num
    if prev is not None:
        sum += prev
    
    print(sum)