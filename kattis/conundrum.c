#include <stdio.h>
#include <stdlib.h>

int main()
{
    char* str = NULL;
    size_t size = 0;
    ssize_t len = getline(&str, &size, stdin);
    if (len % 3 != 0) --len;

    int count = 0;
    for (int i = 0; i < len; i += 3) {
        count += (str[i] != 'P');
    }
    for (int i = 1; i < len; i += 3) {
        count += (str[i] != 'E');
    }
    for (int i = 2; i < len; i += 3) {
        count += (str[i] != 'R');
    }
    free(str);

    printf("%d\n", count);
}
