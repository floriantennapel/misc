from sys import stdin
from heapq import heappush, heappop

def find_max(schedule, k):
    back = schedule[0][0]
    front = back + k

    current = []
    count = len(current)

    while len(schedule) > 0:
        s, e = heappop(schedule)
        heappush(current, (e, s))

        diff = s - front
        back += diff
        front += diff

        while len(current) > 0 and current[0][0] < back:
            heappop(current)

        while len(schedule) > 0 and schedule[0][0] <= front:
            st, en = heappop(schedule)
            heappush(current, (en, st))

        count = max(count, len(current))

        print(back, front)

    return count


n, k = stdin.readline().strip().split()
schedule = []

for _ in range(int(n)):
    s, e = stdin.readline().strip().split() 
    heappush(schedule, (int(s), int(e)))

print(find_max(schedule, int(k)))

