#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    size_t n = 0;
    char *buf = NULL, *key = NULL;
    int key_len = getline(&key, &n, stdin) - 1;
    n = 0;
    getline(&buf, &n, stdin);
    n = 0;
    free(buf);
    buf = NULL;
    int s_len = getline(&buf, &n, stdin) - 1;
    long count = 0;
    for (int i = 0; i <= s_len - key_len; i++) {
        if (memcmp(buf+i, key, key_len) == 0)
            ++count;
    }
    printf("%lu\n", count);
    free(buf);
    free(key);
}
