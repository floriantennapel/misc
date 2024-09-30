#include <stdio.h>

int main()
{
    int n;
    char p, c;

    int count = 0;
    scanf("%d\n", &n);
    for (int i = 0; i < n; i++) {
        scanf("%c\n", &c);
        if (i) count += (p == c);
        p = c;
    }

    printf("%d\n", count);
}