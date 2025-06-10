#include <stdio.h>
#include "c_macros/datastructures/hashmap.h"

typedef struct
{
    char* str;
    int len;
} String;

#define HASH(KEY) (byte_hasher((KEY)->str, (KEY)->len))
#define EQ(A, B) (strcmp((A)->str, (B)->str) == 0)

HASHMAP_DEFINE(Set, String, HASHMAP_NO_VALUE, HASH, EQ)

int main()
{
    Set done = Set_new(0);
    int n;
    scanf("%d\n", &n);
    while (n--) {
        size_t max_n = 0;
        String key = {};
        key.len = getline(&(key.str), &max_n, stdin) - 1;
        key.str[key.len] = '\0';
        if (!Set_contains(&done, &key)) {
            printf("%s\n", key.str);
            Set_insert(&done, key, (HASHMAP_NO_VALUE){});
        }
    }
}
