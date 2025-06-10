#include <stdio.h>

int main()
{
    int n, k, x;
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &x);
        if (i % k == 0)
            printf("%d ", x);
    }
}
