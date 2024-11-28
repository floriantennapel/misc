#include <stdio.h>

int main()
{
    unsigned long n, a, b;
    scanf("%lu %lu %lu", &n, &a, &b);

    unsigned long res = 0;
    for (unsigned long i = 1; i <= 63; i++) {
        int switches = 0;
        unsigned long pow = 1ul << i;
        if (b & pow) {
            switches += b % pow;
        }
        if (a & pow)
            switches += pow - a % pow;
        res |= (switches % 2 == 0)
            ? b & pow
            : (b & pow) ^ pow;
    }
    int swaps = (b % 2 == 0)
        ? (b - a + 1) / 2
        : (b - a) / 2;
    res |= (swaps % 2 == 0)
        ? b & 1ul
        : (b & 1ul) ^ 1ul;
    if (!res)
        puts("Enginn");
    else if (res <= n)
        printf("%lu\n", res);
    else
        puts("Gunnar");
}
