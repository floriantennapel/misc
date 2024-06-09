from sys import stdin


def move(r, c, grid, dir, merged):
    value = grid[r][c]
    params = [(0, -1), (len(grid) - 1, 1)]
    end, step = params[int(dir / 2)]
    start = c if dir % 2 == 0 else r

    for i in range(start, end, step):
        if dir % 2 == 0:
            row = next_row = r
            col = i
            next_col = i + step
        else:
            row = i
            next_row = i + step
            col = next_col = c

        if grid[next_row][next_col] == value and not merged[next_row][next_col]:
            grid[next_row][next_col] = 2*value
            merged[next_row][next_col] = True
            grid[row][col] = 0
            return
        elif grid[next_row][next_col] == 0:
            grid[next_row][next_col] = value
            grid[row][col] = 0
        else:
            return


def move_all(grid, dir, merged):
    params = [(0, len(grid), 1), (len(grid)-1, -1, -1)]
    start, end, step = params[int(dir / 2)] 
    for i in range(start, end, step):
        for j in range(start, end, step):
            move(i, j, grid, dir, merged)


if __name__ == '__main__':
    lines = stdin.read().splitlines()
    grid = [[int(d) for d in line.split()] for line in lines[:-1]]
    merged = [[False for _ in range(4)] for _ in range(4)]

    move_all(grid, int(lines[4]), merged)

    for line in grid:
        print(' '.join(map(str, line)))
