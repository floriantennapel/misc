#include <stdio.h>

int main()
{
    int a, i;
    scanf("%d %d\n", &a, &i);

    for (int b = a * (i-1); ; b++) {
        if ((b / (long double) a) > (i-1)) {
            printf("%d\n", b);
            return 0;
        }
    }
}
