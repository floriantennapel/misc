#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int len = 1000 / 8 + 1;

void set(char* bits, int index)
{
    bits[index / 8] |= 1 << (index % 8);
}

int main()
{
    char learn[len];
    char knows[len];
    char buf[10000];
    memset(learn, '\0', len);
    memset(knows, '\0', len);
    
    int n, k;
    scanf("%d\n", &n);
    
    fgets(buf, 10000, stdin);
    k = atoi(strtok(buf, " \n"));
    set(learn, k);
    for (int i = 1; i < n; i++) {
        k = atoi(strtok(NULL, " \n"));
        set(learn, k);
    }
    
    fgets(buf, 10000, stdin);
    k = atoi(strtok(buf, " \n"));
    set(knows, k);
    for (int i = 2; i < n; i++) {
        k = atoi(strtok(NULL, " \n"));
        set(knows, k);
    }
    
    for (int i = 0; i < 1000; i++) {
        if ((knows[i/8] & 1 << i % 8) != (learn[i/8] & 1 << i % 8)) {
            printf("%d\n", i);
        }
    }
}