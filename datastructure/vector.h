#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

typedef struct vector
{
    size_t capacity;
    size_t size;
    size_t datasize;
    char* arr;
} vector;

/**
 * create a new vector, vector_free must be called after use
 */
vector make_vector(size_t datatype_size);

/**
 * free the memory used by a vector
 */
void vector_free(vector* vec);

/**
 * number of elements stored in the vector
 */
size_t vector_size(vector* vec);

/**
 * get pointer to element at given index
 */
void* vector_get(vector* vec, size_t index);

/**
 * append an element to the end of the vector
 *
 * @param value copied and stored in the vector, does not need to be heap allocated
 */
void vector_push_back(vector* vec, const void* value);

/**
 * remove last element from vector
 */
void vector_pop_back(vector* vec);

/**
 * insert value at given index, moving remaining values further behind 
 *
 * @param value copied and stored in the vector, does not need to be heap allocated
 */
void vector_insert(vector* vec, const void* value, size_t index);

/**
 * remove element at given index, moving remaing values forward
 */
void vector_remove(vector* vec, size_t index);

#endif
