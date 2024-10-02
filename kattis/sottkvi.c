#include <stdio.h>

int main()
{
    int n, k, d, di;
    scanf("%d %d %d\n", &n, &k, &d);

    int count = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d\n", &di);
        count += ((d - di) >= (14 - k));
    }

    printf("%d\n", count);
}
