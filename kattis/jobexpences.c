#include <stdio.h>

int main()
{
    int n;
    long s = 0, k;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%ld", &k);
        if (k < 0)
            s -= k;
    }
    printf("%ld\n", s);
}
