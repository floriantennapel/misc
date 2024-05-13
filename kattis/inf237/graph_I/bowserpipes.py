from heapq import heappush

class Room:
    def __init__(self, index, next_room):
        self.is_entry = True
        self.index = index
        self.next_room = next_room
        
        if next_room == -1:
            self.end_room = index
            self.dist = 0
        else:
            self.end_room = -1
            self.dist = -1
    

    def __lt__(self, other):
        return (self.dist, self.index).__lt__((other.dist, other.index))


    def __eq__(self, other):
        return self.dist == other.dist and self.index == other.index


n = int(input())
rooms = list()
entry_points = [[] for _ in range(n)] 


def dfs(index, is_first_call):
    current = rooms[index]
    if not is_first_call:
        current.is_entry = False
    if current.dist != -1:
        return current

    path = dfs(current.next_room, False)
    current.end_room = path.end_room
    current.dist = path.dist + 1

    return current


def initialize():
    global rooms
    rooms = [Room(i, int(n)) for i, n in enumerate(input().strip().split(' '))]

    for i in range(n):
        dfs(i, True)

    for i in range(n):
        current = rooms[i]
        if current.is_entry:
            heappush(entry_points[current.end_room], current)


def mario_path(start):
    end = rooms[start].end_room 
    return entry_points[end][0].index


initialize()
a = int(input())
for entry in [int(p) for p in input().strip().split(' ')]:
    print(mario_path(entry))
