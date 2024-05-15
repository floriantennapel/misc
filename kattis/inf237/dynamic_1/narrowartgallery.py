memo = dict()

def maxValue(rooms, k, prev):
    n = len(rooms)

    if n == 0:
        return 0
    if (n, k, prev) in memo:
        return memo[(n, k, prev)]
    if k == 0:
        val = sum([sum(pair) for pair in rooms])
        memo[(n, k, prev)] = val
        return val
    if n == k:
        val = max(sum([r[0] for r in rooms]), sum([r[1] for r in rooms]))
        memo[(n, k, prev)] = val
        return val
    
    choices = [sum(rooms[0]) + maxValue(rooms[1:], k, -1)]
    if prev != 1:
        choices.append(rooms[0][1] + maxValue(rooms[1:], k-1, 0))
    if prev != 0:
        choices.append(rooms[0][0] + maxValue(rooms[1:], k-1, 1))

    val = max(choices)
    memo[(n, k, prev)] = val
    return val 


n, k = input().strip().split()
rooms = []
for _ in range(int(n)):
    r1, r2 = input().strip().split()
    rooms.append([int(r1), int(r2)])

print(maxValue(rooms, int(k), -1))
