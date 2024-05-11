from queue import Queue


def rotated(icon):
    return chr((ord(icon) - ord('A') + 1) % 6 + ord('A'))


def do_effect(icon, pos, icons):
    seq = list(icons)
    
    match icon:
        case 'A':
            if pos != 0:
                seq[pos-1] = rotated(seq[pos-1])
            if pos != 7:
                seq[pos+1] = rotated(seq[pos+1])
        case 'B':
            if 0 < pos < 7:
                seq[pos+1] = seq[pos-1]
        case 'C':
            seq[7-pos] = rotated(seq[7-pos])
        case 'D':
            if 0 < pos < 4:
                for i in range(pos):
                    seq[i] = rotated(seq[i])
            elif 3 < pos < 7:
                for i in range(pos+1, 8):
                    seq[i] = rotated(seq[i])
        case 'E':
            if 0 < pos < 7: 
                y = min(7 - pos, pos)
                seq[pos-y] = rotated(seq[pos-y])
                seq[pos+y] = rotated(seq[pos+y])
        case 'F':
            x = 0
            if pos % 2 == 0:
                x = (pos + 10) // 2 - 1
            else:
                x = (pos + 1) // 2 - 1
            seq[x] = rotated(seq[x])
    
    return ''.join(seq)


def get_next(current):
    next = []
    for i in range(8):
        next.append(do_effect(current[i], i, current))
    return next
    

def bfs(start, target):
    visited = set()
    queue = Queue()
    queue.put((start, 0))

    while not queue.empty():
        current = queue.get()
        if current[0] in visited:
            continue
        visited.add(current[0])

        if current[0] == target:
            return current[1]
        
        for n in get_next(current[0]):
            queue.put((n, current[1] + 1))


start = input().strip()
target = input().strip()

print(bfs(start, target))
