#include <stdio.h>

int main()
{
    int g, t, n, wi;
    scanf("%d %d %d\n", &g, &t, &n);

    int sum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d ", &wi); 
        sum += wi;
    }

    printf("%d\n", (g - t) * 9 / 10 - sum);
}
