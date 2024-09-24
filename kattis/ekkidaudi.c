#include <stdio.h>
#include <string.h>

int main()
{
    char l1[2101];
    char l2[2101];

    fgets(l1, 2101, stdin);
    fgets(l2, 2101, stdin);

    char* s1 = strtok(l1, "|");
    char* s3 = strtok(NULL, "\n");
    char* s2 = strtok(l2, "|");
    char* s4 = strtok(NULL, "\n");
    
    printf("%s%s %s%s\n", s1, s2, s3, s4);
}