#include <stdio.h>

#define SWAP(cups, a, b) { int tmp = (cups)[(a)]; (cups)[(a)] = (cups)[(b)]; (cups)[(b)] = tmp; }

int main()
{
    int cups[] = {1, 0, 0};

    char buf[51];
    fgets(buf, 51, stdin);

    for (char* c = buf; *c != '\0'; c++) {
        switch (*c) {
        case 'A':
            SWAP(cups, 0, 1);
            break;
        case 'B':
            SWAP(cups, 1, 2);
            break;
        case 'C':
            SWAP(cups, 0, 2);
        }
    }

    for (int i = 0; i < 3; i++) {
        if (cups[i]) {
            printf("%d\n", i+1);
            return 0;
        }
    }
}