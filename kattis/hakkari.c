#include <stdio.h>

int main()
{
    int n, m;
    char results[100*100][8];
    int ind = 0;
    
    scanf("%d %d\n", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c = getchar();
            if (c == '*') {
                sprintf(results[ind++], "%d %d", i+1, j+1);
            }
        }
        getchar();
    }
    
    printf("%d\n", ind);
    for (int i = 0; i < ind; i++) {
        printf("%s\n", results[i]);
    }
}