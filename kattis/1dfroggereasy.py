_, i, goal = (int(d) for d in input().split())
i -= 1
board = [int(d) for d in input().split()]
visited = [False for _ in board]
steps = 0

while True:
    if i < 0:
        print('left')
        break
    elif i >= len(board):
        print('right')
        break
    elif visited[i]:
        print('cycle')
        break
    
    current = board[i]
    if current == goal:
        print('magic')
        break
    
    visited[i] = True
    i += current
    steps += 1
    

print(steps)
