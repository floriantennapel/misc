#include <stdio.h>

typedef struct Flight
{
    int from;
    int to;
    int cost;
} Flight;

int main()
{
    int n, c;
    scanf("%d\n", &n);

    Flight flights[n*n];
    int size = 0;

    for (int from = 1; from <= n; from++) {
        for (int to = 1; to <= n; to++) {
            scanf("%d", &c);                        
            getchar();

            if (c >= 0) {
                Flight* f = flights + size++;
                f->from = from;
                f->to   = to;
                f->cost = c;
            }
        }
    }

    printf("%d\n", size);
    for (int i = 0; i < size; i++) {
        Flight* f = flights + i; 
        printf("%d %d %d\n", f->from, f->to, f->cost);
    }
}
