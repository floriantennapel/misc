from sys import stdin

merged = [[False for _ in range(4)] for _ in range(4)]

def move(r, c, grid, dir):
    value = grid[r][c]
    params = [(0, -1), (len(grid) - 1, 1)]
    end, step = params[int(dir / 2)]
    start = r if dir % 2 == 1 else c

    for i in range(start, end, step):
        next = i + step

        if dir % 2 == 0:
            if grid[r][next] == value and not merged[r][next]:
                grid[r][next] = 2*value
                merged[r][next] = True
                grid[r][i] = 0
                return
            elif grid[r][next] == 0:
                grid[r][next] = value
                grid[r][i] = 0
            else:
                return
        else:
            if grid[next][c] == value and not merged[next][c]:
                grid[next][c] = 2*value
                merged[next][c] = True
                grid[i][c] = 0
                return
            elif grid[next][c] == 0:
                grid[next][c] = value
                grid[i][c] = 0 
            else:
                return

def move_all(grid, dir):
    params = [(0, len(grid), 1), (len(grid)-1, -1, -1)]
    start, end, step = params[int(dir / 2)] 
    for i in range(start, end, step):
        for j in range(start, end, step):
            move(i, j, grid, dir)


lines = stdin.read().splitlines()
grid = [[int(d) for d in line.split()] for line in lines[:-1]]

move_all(grid, int(lines[4]))

for line in grid:
    print(' '.join(map(str, line)))
