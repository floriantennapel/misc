from sys import stdin

operators = '+-*/'
solutions = dict()
for op1 in operators:
    for op2 in operators:
        for op3 in operators:
            if op1 == op2 == op3 == '/':
                continue
            sol = f'4 {op1} 4 {op2} 4 {op3} 4'
            solutions[int(eval(sol.replace('4 / 4 / 4', '0')))] = sol


for line in stdin.readlines()[1:]:
    n = int(line)
    if n in solutions:
        print(solutions[n], '=', n)
    else:
        print('no solution')
