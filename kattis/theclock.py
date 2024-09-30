clock = dict()
h = 0
m = 0

dm = 3600 // 60
dh = dm // 12

for t in range(12*60):
    angle = (m + 3600 - h) % 3600
    clock[angle] = t

    m += dm
    h += dh

def mins_to_time(mins):
    h = mins // 60
    m = mins % 60
    return f'{h:02}:{m:02}'

a = int(input())
print(mins_to_time(clock[a]))