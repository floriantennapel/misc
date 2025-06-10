#include <stdio.h>

int main()
{
    int n, a, b, count = 0, max = 0; 
    scanf("%d", &n);
    while (n--) {
        scanf("%d %d", &a, &b);
        count += b - a;
        max = count > max ? count : max;
    }
    printf("%d\n", max);
}
