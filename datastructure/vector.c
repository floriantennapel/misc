#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "vector.h"

const int min_capacity = 8;

ivector new_ivector(size_t capacity)
{
    ivector ret;
    ret.capacity = capacity > min_capacity ? capacity : min_capacity;
    ret.size = 0;
    if ((ret.arr = malloc(sizeof(int) * ret.capacity)) == NULL) {
        perror("new_ivector: ");
        exit(1);
    }

    return ret;
}

lvector new_lvector(size_t capacity)
{
    lvector ret;
    ret.capacity = capacity > min_capacity ? capacity : min_capacity;
    ret.size = 0;
    if ((ret.arr = malloc(sizeof(long) * ret.capacity)) == NULL) {
        perror("new_lvector: ");
        exit(1);
    }

    return ret;
}

void ivector_free(ivector* vec) 
{
    free(vec->arr);
}

void lvector_free(lvector* vec) 
{
    free(vec->arr);
}

size_t ivector_size(const ivector* vec) 
{
    return vec->size;
}

size_t lvector_size(const lvector* vec) 
{
    return vec->size;
}

void iresize(ivector* vec, int grow, char* caller)
{
    size_t new_capacity = grow ? vec->capacity * 2 : vec->capacity / 2;

    vec->capacity = new_capacity;
    if ((vec->arr = realloc(vec->arr, new_capacity * sizeof(int))) == NULL) {
        perror(caller);
        exit(1);
    }
}

void lresize(lvector* vec, int grow, char* caller)
{
    size_t new_capacity = grow ? vec->capacity * 2 : vec->capacity / 2;

    vec->capacity = new_capacity;
    if ((vec->arr = realloc(vec->arr, new_capacity * sizeof(long))) == NULL) {
        perror(caller);
        exit(1);
    }
}

void ivector_push_back(ivector *vec, int val)
{
    if (vec == NULL) {
        fprintf(stderr, "ivector_push_back: vector cannot be NULL\n");
    }
    if (vec->size == vec->capacity) {
        iresize(vec, 1, "ivector_push_back: ");
    }

    vec->arr[(vec->size)++] = val;
}

void lvector_push_back(lvector *vec, long val)
{
    if (vec == NULL) {
        fprintf(stderr, "lvector_push_back: vector cannot be NULL\n");
    }
    if (vec->size == vec->capacity) {
        lresize(vec, 1, "lvector_push_back: ");
    }

    vec->arr[(vec->size)++] = val;
}

int ivector_get(const ivector *vec, size_t index)
{
    if (vec == NULL) {
        fprintf(stderr, "ivector_get: vector cannot be NULL\n");
    }
    if (index < 0 || index >= vec->size) {
        fprintf(stderr, "ivector_get: index out of bounds\n");
        exit(1);
    }

    return vec->arr[index];
}

long lvector_get(const lvector *vec, size_t index)
{
    if (vec == NULL) {
        fprintf(stderr, "lvector_get: vector cannot be NULL\n");
    }
    if (index < 0 || index >= vec->size) {
        fprintf(stderr, "lvector_get: index out of bounds\n");
        exit(1);
    }

    return vec->arr[index];
}

int ivector_pop_back(ivector *vec)
{
    if (vec == NULL) {
        fprintf(stderr, "ivector_pop_back: vector cannot be NULL\n");
    }
    if (vec->size == 0) {
        fprintf(stderr, "ivector_pop_back: empty vector\n");
        exit(1);
    }

    int val = vec->arr[--(vec->size)];
    if (vec->capacity > min_capacity && vec->size < vec->capacity / 2) {
        iresize(vec, 0, "ivector_pop_back: ");
    }

    return val;
}

long lvector_pop_back(lvector *vec)
{
    if (vec == NULL) {
        fprintf(stderr, "lvector_pop_back: vector cannot be NULL\n");
    }
    if (vec->size == 0) {
        fprintf(stderr, "lvector_pop_back: empty vector\n");
        exit(1);
    }

    int val = vec->arr[--(vec->size)];
    if (vec->capacity > min_capacity && vec->size < vec->capacity / 2) {
        lresize(vec, 0, "lvector_pop_back: ");
    }

    return val;
}

int ivector_remove(ivector *vec, size_t index)
{
    if (vec == NULL) {
        fprintf(stderr, "ivector_remove: vector cannot be NULL\n");
    }
    if (index < 0 || index >= vec->size) {
        fprintf(stderr, "ivector_remove: index out of bounds\n");
        exit(1);
    }

    int val = vec->arr[index];

    memmove(vec->arr+index, vec->arr+index + 1, sizeof(int) * (vec->size - index - 1));
    if (--(vec->size) < vec->capacity / 2 && vec->capacity > min_capacity) {
        iresize(vec, 0, "ivector_remove: ");
    }

    return val;
}

long lvector_remove(lvector *vec, size_t index)
{
    if (vec == NULL) {
        fprintf(stderr, "lvector_remove: vector cannot be NULL\n");
    }
    if (index < 0 || index >= vec->size) {
        fprintf(stderr, "lvector_remove: index out of bounds\n");
        exit(1);
    }

    long val = vec->arr[index];

    memmove(vec->arr+index, vec->arr+index + 1, sizeof(long) * (vec->size - index - 1));
    if (--(vec->size) < vec->capacity / 2 && vec->capacity > min_capacity) {
        lresize(vec, 0, "lvector_remove: ");
    }

    return val;
}

void ivector_insert(ivector *vec, int value, size_t index)
{
    if (vec == NULL) {
        fprintf(stderr, "ivector_insert: vector cannot be NULL\n");
        exit(1);
    }
    if (index < 0 || index > vec->size) {
        fprintf(stderr, "ivector_insert: index out of bounds\n");
        exit(1);
    }

    if (vec->size == index) {
        ivector_push_back(vec, value);
        return;
    }

    if (vec->size == vec->capacity) {
        iresize(vec, 1, "ivector insert: ");
    }

    memmove(vec->arr + index + 1, vec->arr + index, sizeof(int) * (vec->size - index));
    vec->arr[index] = value;
    ++(vec->size);
}

void lvector_insert(lvector *vec, long value, size_t index)
{
    if (vec == NULL) {
        fprintf(stderr, "lvector_insert: vector cannot be NULL\n");
        exit(1);
    }
    if (index < 0 || index > vec->size) {
        fprintf(stderr, "lvector_insert: index out of bounds\n");
        exit(1);
    }

    if (vec->size == index) {
        lvector_push_back(vec, value);
        return;
    }

    if (vec->size == vec->capacity) {
        lresize(vec, 1, "lvector insert: ");
    }

    memmove(vec->arr + index + 1, vec->arr + index, sizeof(long) * (vec->size - index));
    vec->arr[index] = value;
    ++(vec->size);
}