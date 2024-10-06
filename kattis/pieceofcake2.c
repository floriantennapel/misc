#include <stdio.h>

int main()
{
    long n, h, v;
    scanf("%ld %ld %ld", &n, &h, &v);
    
    if (h < n / 2.) h = n - h; 
    if (v < n / 2.) v = n - v;
    printf("%ld\n", 4 * h * v);
}
