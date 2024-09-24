stack = []

line = input()
for s in line.split():
    if s.isnumeric():
        stack.append(s)
    else:
        b = stack.pop()
        a = stack.pop()
        stack.append(f'({a}{s}{b})')

print(''.join(stack))
