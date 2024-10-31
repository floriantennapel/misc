#include <stdio.h>

int main()
{
    int n, c;
    while (1) {
        scanf("%d", &n);
        if (n == -1) break;

        int graph[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", graph[i]+j);
            }
        } 

        int size = 0;
        int weak[n];
        for (int i = 0; i < n; i++) {
            int is_triangle = 0;

            for (int a = 0; a < n-1; a++) {
                for (int b = a+1; b < n; b++) {
                    if (graph[i][a] && graph[i][b] && graph[a][b]) {
                        is_triangle = 1;
                        goto done;             
                    } 
                } 
            }
        done:
            if (!is_triangle) {
                weak[size++] = i; 
            }
        }
        
        if (size) {
            for (int i = 0; i < size-1; i++) {
                printf("%d ", weak[i]);
            }
            printf("%d\n", weak[size-1]);
        } else 
            puts("");
    }
}
