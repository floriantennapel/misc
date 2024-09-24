from sys import stdin

convert = {'I': 1, 'V': 5, 'X': 10, 'L': 50, 'C': 50, 'D': 500, 'M': 1000}

input()
for line in stdin.read().splitlines():
    stack = [convert[line[0]]]
    prev = convert[line[0]]

    line = line[1:]
    while len(line) > 0:
        c = convert[line[0]]
        line = line[1:]
        


    print(sum(stack))




