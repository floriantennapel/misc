#include <stdio.h>
#include <string.h>
#include "../datastructure/hashmap.h"

typedef struct
{
    int r, c, s;
} PosSteps;

int eq(const PosSteps* a, const PosSteps* b)
{
    return !memcmp(a, b, sizeof(PosSteps));
}

size_t hash(const PosSteps* k)
{
    const int* arr = (int*) k;
    unsigned long hash = 5381;

    for (int i = 0; i < 3; i++) {
        hash = ((hash << 5) + hash) + arr[i]; 
    }

    return hash;
}

DECLARE_HASHMAP(Map, PosSteps, int, eq, hash)

Map memo;
long walk_len(PosSteps key) {
    if (!key.s)
        return !key.c && !key.r;

    int* res;
    if ((res = Map_get(&memo, &key))) 
        return *res;
    
    long sum = 0;
    for (int r = -1; r <= 1; r += 2) {
        for (int c = -1; c <= 1; c += 2) 
            sum += walk_len((PosSteps) {key.r + r, key.c + c, key.s - 1});
    }
    for (int c = -2; c <= 2; c += 4)
        sum += walk_len((PosSteps) {key.r, key.c + c, key.s - 1});

    Map_insert(&memo, key, sum);
    return sum;
}

int main()
{
    int n;
    scanf("%d", &n);
    memo = Map_new(0);
    for (int i = 0; i < n; i++) {
        int m;
        scanf("%d", &m);
        printf("%ld\n",walk_len((PosSteps) {0, 0, m}));
    }
}
