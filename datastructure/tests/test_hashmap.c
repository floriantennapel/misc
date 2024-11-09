#include <string.h>
#include <math.h>

#include "../hashmap.h"

void pass(int i)
{
    printf("\033[0;32m");
    printf("test %d passed\033[0m\n", i);
}

void fail(int i)
{
    printf("\033[0;31m");
    printf("test %d failed\033[0m\n", i);
}

void supress_output()
{
    freopen("/dev/null", "w", stdout);
    freopen("/dev/null", "w", stderr);
}

typedef struct 
{
    char s[40];
} Str;

int eq(const Str* a, const Str* b)
{
    return !strcmp(a->s, b->s);
}

// djb2 hashing function
size_t hash(const Str* str)
{
    const char* s = str->s;
    size_t h = 5381;
    int c;
    while ((c = *s++))
        h = ((h << 5) + h) + c;
    return h; 
}
// terrible hashing function
// size_t hash(const Str* str) { return 0; }

const Str words[] = { 
    (Str){"these"}, 
    (Str){"are"}, 
    (Str){"a"}, 
    (Str){"bunch"}, 
    (Str){"of"}, 
    (Str){"testing"}, 
    (Str){"words"}
};

DECLARE_HASHMAP(SIMap, Str, int, eq, hash)

int initial_capacity_is_2pow()
{
    SIMap a = SIMap_new(-1); 
    if (a.capacity == -1) return 0;
    double diff = a.capacity - log2(a.capacity);
    diff = (diff < 0) ? -diff : diff;
    if (diff - (int)diff > 0.000001) return 0;
    SIMap_free(&a);

    SIMap b = SIMap_new(256);
    if (b.capacity != 256) return 0;
    SIMap_free(&b);

    SIMap c = SIMap_new(257);
    if (c.capacity != 512) return 0;
    SIMap_free(&c);

    return 1;
}

int contains_key_test()
{
    SIMap m = SIMap_new(0);
    Str a = {"test"};
    if (SIMap_contains_key(&m, &a)) return 0;
    SIMap_insert(&m, a, 42);
    if (!SIMap_contains_key(&m, &a)) return 0;

    
    for (int i = 0; i < sizeof(words) / sizeof(Str); i++) {
        SIMap_insert(&m, words[i], i);
    }

    for (int i = 0; i < sizeof(words) / sizeof(Str); i++) {
        if (!SIMap_contains_key(&m, words+i)) return 0;
    }
    
    const Str* keys[m.size];
    SIMap_all_keys(&m, keys);
    
    for (int i = 0; i < m.size; i++) {
        if (!SIMap_contains_key(&m, keys[i])) return 0;
    }
    
    // saving all keys onto stack
    Str saved_keys[m.size];
    for (int i = 0; i < m.size; i++) {
        saved_keys[i] = *keys[i];
    }

    int keys_size = m.size;
    for (int i = 0; i < keys_size; i++) {
        SIMap_remove(&m, saved_keys+i);
        if (SIMap_contains_key(&m, saved_keys+i)) return 0;
        if (m.size != keys_size - i - 1) return 0;
        for (int j = i+1; j < keys_size; j++) {
            if (!SIMap_contains_key(&m, saved_keys+j)) return 0;
        }
    }

    if (m.size > 0) return 0;

    SIMap_free(&m);
    return 1;
}

int double_insert_only_changes_value()
{
    const int n = sizeof(words) / sizeof(Str);

    SIMap m = SIMap_new(0);
    for (int i = 0; i < n; i++) {
        SIMap_insert(&m, words[i], i);
    }
    if (m.size != n) return 0;
    for (int i = 0; i < n; i++) {
        SIMap_insert(&m, words[i], i+1);
    }
    if (m.size != n) return 0;
    for (int i = 0; i < n; i++) {
        if (*SIMap_get(&m, words+i) != i+1) return 0;
    }

    SIMap_free(&m);
    return 1;
}

int int_eq(const int* a, const int* b) { return *a == *b; }
size_t int_hash(const int* k) { return *k; }
typedef struct {} None;
DECLARE_HASHMAP(ISet, int, None, int_eq, int_hash)

// run program using valgrind
int leak_test()
{
    ISet set = ISet_new(1 << 20); // adjust value for different testing purposes, valgrind will use ages with high values
    None n;
    int n_elems = set.capacity * 0.75;
    for (int i = 0; i < n_elems; i++) {
        if (ISet_get(&set, &i)) return 0;
        ISet_insert(&set, i, n);
    } 
    if (set.size != n_elems) return 0;
    for (int i = 0; i < n_elems; i++) {
        if (!ISet_get(&set, &i)) return 0;
    }

    ISet_free(&set);
    return 1;
}

int main()
{
    int test_counter = 0;
    int pass_counter = 0;

    int (*tests[])() = {
        initial_capacity_is_2pow,
        contains_key_test,
        double_insert_only_changes_value,
        leak_test
    };

    for (int i = 0; i < sizeof(tests) / sizeof(void*); i++) {
        ++test_counter;
        if (tests[i]()) {
            ++pass_counter;
            pass(test_counter);
        } else fail(test_counter);
    }
    
    printf("\n************************\n * %2d/%2d tests passed * \n************************\n", pass_counter, test_counter);
    puts("remember to re-run tests with bad hash function");
}
