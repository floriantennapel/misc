from math import sqrt, inf

def normalize(t):
    x, y, a, b, c = t
    l = sqrt(x**2 + y**2)
    return (x/l, y/l, a, b, c)

n, t = (int(d) for d in input().split())

readings = []
for _ in range(n):
    readings.append(tuple(int(d) for d in input().split(' ')))

dist = 0.
vectors = []
prev = None
dt = None
for x, y, ti in readings:
    if prev is not None:
        px, py, pti = prev
        dist += sqrt((x-px)**2 + (y-py)**2)
        vectors.append((x-px, y-py, pti, px, py))
        if dt is None:
            dt = dist / ti
    prev = (x, y, ti)

vectors = [normalize(v) for v in vectors]

gps = []
prev = None
i = 0.
while True:
    if (i > vectors[-1][2]):
        break
    prev = vectors[0]
    for vx, vy, ti, x, y in vectors[1:]:
        if ti >= i:
            break
        prev = (vx, vy, ti, x, y)
    vx, vy, ti, x, y = prev
    gps.append((x + (i - ti)*vx, y + (i - ti)*vy))
    #print(f'{x} + {i-ti}*{vx} = {x + (i-ti)*vx}')
    #print((x + (i - ti)*vx, y + (i - ti)*vy))

    i += dt

gps.append(readings[-1][:2])

dg = 0
prev = None
for x, y in gps:
    if prev is not None:
        px, py = prev
        dg += sqrt((x-px)**2 + (y-py)**2)
    prev = (x, y)

print(dist)
print(dg)
print((dist - dg) / dist)








