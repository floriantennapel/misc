#include <stdio.h>
#include <string.h>

void drop_down(char* grid, int n, int m, int r, int c)
{
    for (int i = r; i < n-1; i++) {
        int ind = i*m + c;
        if (grid[ind+m] == '.') {
            char tmp = grid[ind];
            grid[ind] = grid[ind+m];
            grid[ind+m] = tmp;
        } else return;
    }
}

int main()
{
    int n, m;
    scanf("%d %d\n", &n, &m);

    char grid[n*m];
    char buf[m+2];
    for (int i = 0; i < n; i++) {
        fgets(buf, m+2, stdin);
        memcpy(grid+i*m, buf, m);
    }

    for (int r = n-2; r >= 0; r--) {
        for (int c = 0; c < m; c++) {
            if (grid[r*m + c] == 'S') {
                drop_down(grid, n, m, r, c);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            putchar(grid[i*m+j]);
        }
        putchar('\n');
    }
}
