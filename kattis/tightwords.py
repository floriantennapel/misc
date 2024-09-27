from sys import stdin

memo = dict()
def count_tight_r(front, l, k, n):
    if l == n:
        return 1
    
    key = (front, k, n-l)
    if key in memo:
        return memo[key]
    
    s = sum(count_tight_r(f, l+1, k, n) for f in range(max(0, front-1), min(k, front+1)+1))
    
    memo[key] = s
    return s

def count_tight(k, n):
    return sum(count_tight_r(f, 1, k, n) for f in range(k+1))

for line in stdin:
    k, n = (int(d) for d in line.split())
    print(100 * count_tight(k, n) / (k+1)**n)