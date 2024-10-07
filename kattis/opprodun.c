#include <stdio.h>

int main()
{
    int n, m;
    scanf("%d\n%d", &n, &m);
    
    int base = m / n;
    int rem = m % n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < base; j++) putchar('*');
        if (i < rem) putchar('*');
        putchar('\n');
    }
}
