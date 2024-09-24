#include <stdio.h>
#include <stdlib.h>

#define SWAP(buf, a, b) { int tmp = (buf)[(a)]; (buf)[(a)] = (buf)[(b)]; (buf)[(b)] = tmp; }

int main()
{
    char buf[8];
    fgets(buf, 8, stdin);
    SWAP(buf, 0, 2);
    SWAP(buf, 4, 6);

    int a = atoi(buf);
    int b = atoi(buf+4);
    printf("%d\n", (a > b) ? a : b);
}