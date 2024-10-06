#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int found = 0;
    char* str = NULL;
    size_t size = 0;
    for (int i = 1; getline(&str, &size, stdin) != -1; i++) {
        if (strstr(str, "FBI")) {
            found = 1;
            printf("%d ", i);
        }
    }

    free(str);

    if (!found) printf("HE GOT AWAY!");
    puts("");
}
