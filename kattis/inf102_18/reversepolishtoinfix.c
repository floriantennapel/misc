#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char buf[11];
    char* tok;

    char** stack = malloc(200000 * sizeof(char*));
    int top = -1;

    while (scanf("%s ", buf) != EOF) {
        tok = malloc(strlen(buf) + 1);
        strcpy(tok, buf);
        if (tok[0] < '0' || tok[0] > '9') {
            char* s = malloc(strlen(stack[top]) + strlen(stack[top-1]) + 4);
            sprintf(s, "(%s%s%s)", stack[top-1], tok, stack[top]);

            free(tok);
            free(stack[top-1]);
            free(stack[top]);
            stack[--top] = s;
        } else {
            stack[++top] = tok;
        }
    }

    while (top >= 0) {
        printf("%s", stack[top]);
        free(stack[top--]);
    }
    puts("");
    free(stack);
}
