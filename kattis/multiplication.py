def print_lattice(a, b):
    str_a = str(a)
    str_b = str(b)
    result = str(a*b)
    
    print('+' + '-'*(4*len(str_a) + 3) + '+')
        
    print('|   ', end='')
    for d in str_a:
        print(d + 3*' ', end='')
    print('|')
    
    for i, b_digit in enumerate(str_b):
        print('| +', end='')
        for d in str_a:
            print('---+', end='')
        print(' |')
        
        print(f"|{'/' if len(result) > len(str_a) + len(str_b) - i else ' '}|", end='')
        for d in str_a:
            print(str(int(d)*int(b_digit)).zfill(2)[0] + ' /|', end='')
        print(' |')

        print(f"| {'| / '*len(str_a)}|{b_digit}|")

        print('|', end='')
        if (len(result) > len(str_a) + (len(str_b) - i - 1)):
            print(result[-len(str_a) - len(str_b) + i] + '|', end='')
        else:
            print(' |', end='')
        for d in str_a:
            print('/ ' + str(int(d)*int(b_digit)).zfill(2)[1] + '|', end='')
        print(' |')
    
    print(f"| +{'---+'*len(str_a)} |")

    print(f"|{'/' if len(result) > len(str_a) else ' '} ", end='')
    for i in range(len(str_a)-1):
        print(f'{result[-len(str_a) + i]} / ', end='')
    print(result[-1] + '    |')

    print('+' + '-'*(4*len(str_a) + 3) + '+')

        
while True:
    a, b  = (int(d) for d in input().split())
    if (a == b == 0):
        break

    print_lattice(a, b)
