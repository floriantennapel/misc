#include <stdio.h>

int main()
{
    int p, s, m, l;
    scanf("%d %d %d", &m, &p, &s);
    while (s--) {
        scanf("%d", &m);
        int found = 0;
        while (m--) {
            scanf("%d", &l); 
            if (l == p && !found) {
                puts("KEEP");
                found = 1;
            }
        }
        if (!found)
            puts("REMOVE");
    }
}
