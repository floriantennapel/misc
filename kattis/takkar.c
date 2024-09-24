#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int words;
    char* line = NULL;
    size_t max_chars = 0;

    scanf("%d\n", &words);
    getline(&line, &max_chars, stdin);
    
    char* word = strtok(line, " ");
    for (int i = 0; i < words; i++) {
        char first = word[0];
        if (first >= 'A' && first <= 'Z') {
            printf("%c", first);
        }
        word = strtok(NULL, " ");
    }
    puts("");
    free(line);
}
