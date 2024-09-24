t = int(input())

for i in range(t):
    input()
    n = int(input())
    candy_sum = 0
    for j in range(n):
        candy_sum += int(input())
    print('YES' if candy_sum % n == 0 else 'NO')
