#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LL
{
    char name[23];
    struct LL* next;
} LL;

int initials(const char* name)
{
    char f = *name;
    for (; *name != ' '; name++) { /* do nothing */ }
    char l = *(name+1);

    return (f-'A')*26 + (l-'A');
}

void insert(LL** map, const char* name)
{
    int key = initials(name);
    LL* new = malloc(sizeof(LL));
    memcpy(new->name, name, 23);

    LL* current = map[key];

    if (!current) {
        map[key] = new;
    } else {
        for (; current->next; current = current->next) { /* do nothing */ }
        current->next = new;
    }
}

int main()
{
    int n, q;
    scanf("%d %d\n", &n, &q);

    LL** map = calloc(26*26, sizeof(LL*));

    char buf[23];
    for (int i = 0; i < n; i++) {
        fgets(buf, 23, stdin);
        insert(map, buf);
    }

    for (int i = 0; i < q; i++) {
        char f = getchar();
        char l = getchar();
        getchar();

        int key = (f-'A')*26 + (l-'A');
        LL* match = map[key];

        if (!match) puts("nobody");
        else if (!match->next) printf("%s", match->name);
        else puts("ambiguous");
    }  
}

