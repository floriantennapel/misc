#include <stdio.h>

int main()
{
    int n;
    unsigned long sum = 0, start, stop;
    scanf("%d", &n);
    if (n % 2 == 1)
        puts("still running");
    else {
        for (int i = 0; i < n/2; i++) {
            scanf("%lu\n%lu", &start, &stop);
            sum += stop - start;
        }
        printf("%lu\n", sum);
    }
}
