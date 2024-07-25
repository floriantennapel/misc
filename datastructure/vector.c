#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "vector.h"

#define MIN_SIZE 10

void check_and_grow(vector* vec)
{
    if (vec->capacity < vec->size * vec->datasize + vec->datasize) {
        vec->capacity *= 2;
        vec->arr = realloc(vec->arr, vec->capacity);
        if (!vec->arr) {
            perror("vector.c, check_and_grow:");
            exit(1);
        }
    }
}

void check_and_shrink(vector* vec) 
{
    if (vec->capacity < MIN_SIZE * 2 * vec->datasize) {
        return;
    }

    if (vec->size * vec->datasize < vec->capacity / 2) {
        vec->capacity /= 2;
        vec->arr = realloc(vec->arr, vec->capacity);
        if (!vec->arr) {
            perror("vector.c, check_and_shrink:");
            exit(1);
        }
    }

}

vector make_vector(size_t datatype_size)
{
    vector v;
    v.size = 0;
    v.datasize = datatype_size;
    v.capacity = MIN_SIZE * datatype_size;
    v.arr = malloc(v.capacity);
    if (!v.arr) {
        perror("make_vector:");
        exit(1);
    }

    return v;
}

void vector_free(vector* vec)
{
    free(vec->arr);
}


size_t vector_size(vector* vec)
{
    return vec->size;
}

void* vector_get(vector* vec, size_t index)
{
    if (index < 0 || index >= vec->size) {
        fprintf(stderr, "vector_get: index out of bounds\n");
        exit(1);
    }

    return vec->arr + index * vec->datasize;
}

void vector_push_back(vector* vec, const void* value)
{
    check_and_grow(vec);
    memcpy(vec->arr + vec->size * vec->datasize, value, vec->datasize);
    ++(vec->size);
}

void vector_pop_back(vector* vec) 
{
    if (vec->size < 1) {
        fprintf(stderr, "vector_pop_back: empty vector\n");
        exit(1);
    }
    
    --(vec->size);
    check_and_shrink(vec);
    }

void vector_insert(vector *vec, const void *value, size_t index)
{
    if (index < 0 || index > vec->size) {
        fprintf(stderr, "vector_insert: index out of bounds\n");
        exit(1);
    }

    if (index == vec->size) {
        vector_push_back(vec, value);
        return;
    }

    check_and_grow(vec);
    
    memmove(
        vec->arr + (index + 1) * vec->datasize, 
        vec->arr + index * vec->datasize,
        vec->size - index
    );

    memcpy(vec->arr + index * vec->datasize, value, vec->datasize);
    ++(vec->size);
}

void vector_remove(vector* vec, size_t index)
{
    if (index < 0 || index >= vec->size) {
        fprintf(stderr, "vector_remove: index out of bounds\n");
        exit(1);
    }

    if (index == vec->size - 1) {
        vector_pop_back(vec);
        return;
    }

    --(vec->size);
    memmove(
        vec->arr + index * vec->datasize, 
        vec->arr + (index + 1) * vec->datasize, 
        (vec->size - index) * vec->datasize
    );

    check_and_shrink(vec);
}
