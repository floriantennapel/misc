from heapq import heappush, heappop

read_q = []
gift_q = []

n, m, k = (int(d) for d in input().split())

heappush(read_q, ("JaneEyre", k))
for _ in range(n):
    splitted = input().split('"')
    if len(splitted) != 3:
        title = ''.join(splitted[1:-1])
    else:
        title = splitted[1]
    pages = int(splitted[-1])

    heappush(read_q, ((title), pages))

for _ in range(m):
    splitted = input().split('"')
    if len(splitted) != 3:
        title = ''.join(splitted[1:-1])
    else:
        title = splitted[1]

    t = int(splitted[0])
    pages = int(splitted[-1])

    if t == 0:
        heappush(read_q, ((title), pages))
    else:
        heappush(gift_q, (t, (title), pages))

time = 0
while len(read_q) > 0:
    title, pages = heappop(read_q)
    time += pages 

    if title == "JaneEyre":
        print(time)
        exit(0)

    while len(gift_q) > 0 and gift_q[0][0] <= time:
        heappush(read_q, heappop(gift_q)[1:])

