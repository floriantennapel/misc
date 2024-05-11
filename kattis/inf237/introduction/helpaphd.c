#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LEN 11

int main() {
    int a, b;
    char line[LINE_LEN];
    
    // ignoring first line
    fgets(line, LINE_LEN, stdin);
    
    while (fgets(line, LINE_LEN, stdin)) {
        if (line[0] == 'P') {
            puts("skipped");
            continue;
        }
        
        a = atoi(strtok(line, "+"));
        b = atoi(strtok(NULL, "\n"));
        printf("%d\n", a + b);
    }
}
