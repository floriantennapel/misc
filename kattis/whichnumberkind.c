#include <stdio.h>
#include <math.h>

int is_square(int n) 
{
    int root = sqrt(n);
    return (root*root == n) || ((root+1)*(root+1) == n);
}

int main()
{
    int t, n;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        int is_empty = 1;
        scanf("%d", &n);
        if (n % 2 == 1) {
            is_empty = 0;
            printf("O");
        }
        if (is_square(n)) {
            is_empty = 0;
            printf("S");
        }
        if (is_empty)
            printf("EMPTY");
        puts("");
    }
}
