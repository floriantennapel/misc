#include <stdio.h>
#include <stdlib.h>

int main()
{
    int* count = calloc(100, sizeof(int));
    char buf[20];
    int k = 0;
    fgets(buf, 20, stdin);
    for (int i = 0; i < 5; i++) {
        char c = buf[i*3];
        if (++count[c] > k) k = count[c];
    }

    printf("%d\n", k);
    free(count);
}
