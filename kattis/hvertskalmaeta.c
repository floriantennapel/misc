#include <stdio.h>
#include <string.h>
#include "c_macros/datastructures/hashmap.h"

typedef struct
{
    char chars[20];
} String;

#define HASH(key) (byte_hasher(*(key), strlen(*(key))))
#define EQ(a, b) (strcmp(*(a), *(b)) == 0)

HASHMAP_DEFINE(Map, char*, const char*, HASH, EQ)

const char *rey = "Reykjavik", *aku = "Akureyri";

int main()
{
    Map closest = Map_new(0);
    Map_insert(&closest, "Reykjavik", rey);
    Map_insert(&closest, "Kopavogur", rey);
    Map_insert(&closest, "Hafnarfjordur", rey);
    Map_insert(&closest, "Reykjanesbaer", rey);
    Map_insert(&closest, "Akureyri", aku);
    Map_insert(&closest, "Gardabaer", rey);
    Map_insert(&closest, "Mosfellsbaer", rey);
    Map_insert(&closest, "Arborg", rey);
    Map_insert(&closest, "Akranes", rey);
    Map_insert(&closest, "Fjardabyggd", aku);
    Map_insert(&closest, "Mulathing", aku);
    Map_insert(&closest, "Seltjarnarnes", rey);

    char buf[20];
    scanf("%s", buf);
    const char* key = buf;
    printf("%s\n", Map_search(&closest, &key, 0)->value);
}
