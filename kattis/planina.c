#include <stdio.h>

int main()
{
    int n;
    scanf("%d\n", &n);
    
    long side_len = 2;
    for (int i = 0; i < n; i++) {
        side_len += side_len-1;
    }

    printf("%ld\n", side_len*side_len);
}
