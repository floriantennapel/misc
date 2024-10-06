#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_SIZE 3000

typedef struct LL
{
    short val[5];
    int count;
    struct LL* next;
} LL;

void sort(short* cs)
{
    for (int i = 0; i < 5; i++) {
        for (int j = i; j >= 0 && cs[j-1] > cs[j]; j--) {
             short tmp = cs[j];
             cs[j]   = cs[j-1];
             cs[j-1] = tmp;
        }
    }
}

size_t hash(const short* cs)
{
    size_t h = 0;
    for (int i = 0; i < 5; i++) {
        h = (h << 9) + cs[i];
    }

    return h;
}

int* get(LL** map, const short* key)
{
    int h = hash(key) % MAP_SIZE;
    LL* node = map[h];
    LL* prev = NULL;
    while (node) {
        if (!memcmp(node->val, key, 5*sizeof(short)))
            return &node->count;
        prev = node;
        node = node->next;
    }

    LL* new = malloc(sizeof(LL));
    memcpy(new->val, key, sizeof(short) * 5); 
    new->count = 0;
    new->next = NULL;

    if (!prev) map[h] = new;
    else prev->next = new;

    return &new->count;
}

int main()
{
    int n;
    short tmp[5];
    scanf("%d\n", &n);

    LL** map = calloc(MAP_SIZE,  sizeof(LL*));

    int max = 0;
    for (int i = 0; i < n; i++) {
        scanf("%hd %hd %hd %hd %hd\n", tmp, tmp+1, tmp+2, tmp+3, tmp+4);
        sort(tmp);
        int* count = get(map, tmp);
        if (++*count > max) max = *count;
    }

    int sum = 0;
    for (int i = 0; i < MAP_SIZE; i++) {
        LL* node = map[i];
        while (node) {
            if (node->count == max) sum += max;
            node = node->next;
        }
    }

    // not freeing memory for speed, this is a kattis task after all

    printf("%d\n", sum);
}
