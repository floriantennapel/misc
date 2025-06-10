#include <stdio.h>

char buf[52];
int main()
{
    int counts[26] = {};
    fgets(buf, 52, stdin);
    for (char* c = buf; *c; c++)
        counts[*c - 'a']++;
    for (int i = 0; i < 26; i++) {
        if (counts[i] > 1) {
            puts("0");
            return 0;
        }
    }
    puts("1");
}
