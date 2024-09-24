#include <stdio.h>

int main()
{
    int n, m;
    scanf("%d %d\n", &n, &m);

    int map[n*m];
    for (int i = 0; i < n*m; i++) {
        scanf("%d", map + i);
        getchar();
    }

    for (int i = 1; i < n-1; i++) {
        for (int j = 1; j < m-1; j++) {
            int c = map[i*m + j];
            if (c < map[i*m + j - 1] && c < map[i*m + j + 1] && c < map[(i+1)*m + j] && c < map[(i-1)*m + j]) {
                puts("Jebb");
                return 0;
            }
        }
    }

    puts("Neibb");
}