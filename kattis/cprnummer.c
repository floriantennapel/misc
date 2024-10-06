#include <stdio.h>

int main()
{
    const int mul[] = { 4, 3, 2, 7, 6, 5, 0, 4, 3, 2, 1 };
    char buf[13];
    fgets(buf, 13, stdin);

    int sum = 0;
    for (int i = 0; i < 11; i++) {
        sum += (buf[i] - '0') * mul[i];
    }

    printf("%d\n", sum % 11 == 0);
}
