#include <stdio.h>
#include <string.h>

int back = 0;

int contains(char** words, char* word)
{
    for (int i = 0; i < back; i++) {
        if (!strcmp(words[i], word)) return 1;
    }

    return 0;
}

int main()
{
    char buf[82];
    fgets(buf, 82, stdin);

    char* words[41];

    char* word = strtok(buf, " \n"); 
    while (word) {
        if (contains(words, word)) {
            puts("no");
            return 0;
        } 

        words[back++] = word;
        word = strtok(NULL, " \n");
    }

    puts("yes");
}
