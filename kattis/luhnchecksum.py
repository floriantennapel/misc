def is_luhn(s):
    check = lambda i: i % 2 == 0 if len(s) % 2 == 0 else i % 2 == 1

    nums = []
    for i, c in enumerate(s):
        d = int(c)
        if check(i):
            if d * 2 < 10:
                nums.append(d*2)
            else:
                both = str(d*2)
                nums.append(int(both[0]) + int(both[1]))
        else:
            nums.append(d)
        
    return sum(nums) % 10 == 0

n = int(input())

for _ in range(n):
    s = input().strip()
    print('PASS' if is_luhn(s) else 'FAIL')