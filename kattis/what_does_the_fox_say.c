#include <stdlib.h>
#include <stdio.h>

#define DECLARE_HASHMAP(HASHMAP_NAME, HASHMAP_KEYTYPE, HASHMAP_VALTYPE, HASHMAP_KEY_EQ, HASHMAP_HASH) \
    typedef struct _##HASHMAP_NAME##Entry \
    { \
        HASHMAP_KEYTYPE key; \
        HASHMAP_VALTYPE value; \
        struct _##HASHMAP_NAME##Entry* next; \
    } _##HASHMAP_NAME##Entry; \
    \
    typedef struct \
    { \
        size_t capacity; \
        size_t size; \
        _##HASHMAP_NAME##Entry** arr; \
    } HASHMAP_NAME; \
    \
    HASHMAP_NAME HASHMAP_NAME##_new(long initial_capacity) \
    { \
        long capacity; \
        for (capacity = 16; capacity < initial_capacity; capacity <<= 1) {} \
        HASHMAP_NAME ret = { .capacity = capacity, .size = 0 }; \
        if (!(ret.arr = calloc(capacity, sizeof(void*)))) { \
            perror(#HASHMAP_NAME "_new, calloc"); \
            exit(1); \
        } \
        return ret; \
    } \
    \
    void _##HASHMAP_NAME##_free_ll(_##HASHMAP_NAME##Entry* e) \
    { \
        if (!e) return; \
        _##HASHMAP_NAME##_free_ll(e->next); \
        free(e); \
    } \
    \
    void HASHMAP_NAME##_free(HASHMAP_NAME* map) \
    { \
        if (!map || !map->arr) return; \
        for (size_t i = 0; i < map->capacity; i++) \
             _##HASHMAP_NAME##_free_ll(map->arr[i]); \
        free(map->arr); \
        map->arr = NULL; \
    } \
    \
    _##HASHMAP_NAME##Entry* _##HASHMAP_NAME##_get_entry(const HASHMAP_NAME* map, const HASHMAP_KEYTYPE* key) \
    { \
        size_t ind = HASHMAP_HASH(key) % map->capacity; \
        _##HASHMAP_NAME##Entry* current; \
        for (current = map->arr[ind]; current; current = current->next) \
            if (HASHMAP_KEY_EQ(&(current->key), key)) break; \
        return current; \
    } \
    \
    int HASHMAP_NAME##_contains_key(const HASHMAP_NAME* map, const HASHMAP_KEYTYPE* key) \
    { \
        if (!map) { \
            fprintf(stderr, #HASHMAP_NAME "_contains_key, map cannot be NULL\n"); \
            exit(1); \
        } \
        return _##HASHMAP_NAME##_get_entry(map, key) != NULL; \
    } \
    \
    void HASHMAP_NAME##_insert(HASHMAP_NAME* map, HASHMAP_KEYTYPE key, HASHMAP_VALTYPE value) \
    { \
        if (!map) { \
            fprintf(stderr, #HASHMAP_NAME "_insert, map cannot be NULL\n"); \
            exit(1); \
        } \
        size_t ind = HASHMAP_HASH(&key) % map->capacity; \
        _##HASHMAP_NAME##Entry** prev = map->arr + ind; \
        _##HASHMAP_NAME##Entry* current; \
        while ((current = *prev)) { \
            if (HASHMAP_KEY_EQ(&current->key, &key)) { \
                current->value = value; \
                return; \
            } \
            prev = &((*prev)->next); \
        } \
        \
        _##HASHMAP_NAME##Entry* new_entry; \
        if (!(new_entry = malloc(sizeof(_##HASHMAP_NAME##Entry)))) { \
            perror(#HASHMAP_NAME "_insert, malloc"); \
            exit(1); \
        } \
        *new_entry = (_##HASHMAP_NAME##Entry) { .key = key, .value = value, .next = NULL }; \
        *prev = new_entry; \
        ++(map->size); \
    } \
    \
    HASHMAP_VALTYPE* HASHMAP_NAME##_get(const HASHMAP_NAME* map, const HASHMAP_KEYTYPE* key) \
    { \
        if (!map) { \
            fprintf(stderr, #HASHMAP_NAME "_get, map cannot be NULL\n"); \
            exit(1); \
        } \
        \
        _##HASHMAP_NAME##Entry* entry = _##HASHMAP_NAME##_get_entry(map, key); \
        if (!entry) \
            return NULL; \
        else \
            return &(entry->value); \
    } \
    \
    void HASHMAP_NAME##_all_keys(const HASHMAP_NAME* map, const HASHMAP_KEYTYPE** arr) \
    { \
        if (!map) { \
            fprintf(stderr, #HASHMAP_NAME "_all_keys, map cannot be NULL\n"); \
            exit(1); \
        } \
        if (!arr) { \
            fprintf(stderr, #HASHMAP_NAME "_all_keys, arr cannot be NULL\n"); \
            exit(1); \
        } \
        size_t ind = 0; \
        for (size_t i = 0; i < map->capacity; i++) { \
            _##HASHMAP_NAME##Entry* current = map->arr[i]; \
            while (current) { \
                arr[ind++] = &(current->key); \
                current = current->next; \
            } \
        } \
    } \
    \
    void HASHMAP_NAME##_remove(HASHMAP_NAME* map, const HASHMAP_KEYTYPE* key) \
    { \
        if (!map) { \
            fprintf(stderr, #HASHMAP_NAME "_remove, map cannot be NULL\n"); \
            exit(1); \
        } \
        size_t ind = HASHMAP_HASH(key) % map->capacity; \
        _##HASHMAP_NAME##Entry** prev = map->arr + ind; \
        _##HASHMAP_NAME##Entry* current; \
        while ((current = *prev)) { \
            if (HASHMAP_KEY_EQ(&(current->key), key)) { \
                *prev = current->next; \
                free(current); \
                --(map->size); \
                return; \
            } \
            prev = &((*prev)->next); \
        } \
    }

#include <string.h>

typedef struct {} None;
typedef struct 
{
    char s[101];
} Str;

int eq(const Str* a, const Str* b) { return !strcmp(a->s, b->s); }

size_t hash(const Str* str)
{
    char* s = (char*) str->s;
    size_t hash = 5381;
    int c;

    while ((c = *s++))
        hash = ((hash << 5) + hash) + c;

    return hash;   
}

DECLARE_HASHMAP(Set, Str, None, eq, hash);

int main()
{
    int t;
    scanf("%d\n", &t);
    int words_len = 101*100 + 3;
    int animal_len = 108;
    char words[words_len];
    char animal[animal_len];
    None n;

    for (int i = 0; i < t; i++) {
        fgets(words, words_len, stdin);
        Set set = Set_new(100);
        while (1) {
            fgets(animal, animal_len, stdin);
            if (strstr(animal, "what does the fox say?")) break;

            char* w = strstr(animal, " goes ") + 6;
            w = strtok(w, " \n");
            Str s;
            strcpy(s.s, w);
            Set_insert(&set, s, n);
        } 

        char* w = strtok(words, " \n");
        while (w) {
            Str s;
            strcpy(s.s, w);
            if (!Set_contains_key(&set, &s))
                printf("%s ", w);
            w = strtok(NULL, " \n");
        }
        puts("");
        Set_free(&set);
    }
}
