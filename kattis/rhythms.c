#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);

    int groups = n / 2;
    int rem = n % 2;

    printf("%d\n", groups);
    for (int i = 0; i < groups; i++) {
        printf("%d ", ((i < rem) ? 3 : 2));
    }
    puts("");
}
