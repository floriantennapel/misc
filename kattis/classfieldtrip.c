#include <stdio.h>

void remove_n(char* str) {
    for (char* c = str; *c; c++) {
        if (*c == '\n') *c = '\0';
    }
}

int main() 
{
    char a[102];
    char b[102];
    char c[201];
    fgets(a, 102, stdin);
    fgets(b, 101, stdin);

    remove_n(a);
    remove_n(b);

    int i = 0;
    char* ac = a;
    char* bc = b;

    while (*ac || *bc) {
        if      (!*ac) c[i++] = *(bc++);
        else if (!*bc) c[i++] = *(ac++);
        else {
            if (*ac < *bc) c[i++] = *(ac++);
            else           c[i++] = *(bc++);
        } 
    }
    c[i] = '\0';

    printf("%s\n", c);
}
