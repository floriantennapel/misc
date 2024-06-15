#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

typedef struct {
    size_t size;
    size_t capacity;
    int* arr;
} ivector;

typedef struct {
    size_t size;
    size_t capacity;
    long* arr;
} lvector;

/**
 * initialices a new vector containg values of type int (or any other type of same size after casting)
 * remember to call ivector_free when done
 * 
 * @param capacity initial capacity or 0 for default
 */
ivector new_ivector(size_t capacity);

/**
 * initialices a new vector containg values of type long (or any other type of same size after casting)
 * remember to call lvector_free when done
 * 
 * @param capacity initial capacity or 0 for default
 */
lvector new_lvector(size_t capacity);

/**
 * deallocate memory used by ivector
 */
void ivector_free(ivector* vec);

/**
 * deallocate memory used by lvector
 */
void lvector_free(lvector* vec);

/**
 * number of elements stored in vector
 */
size_t ivector_size(const ivector* vec);

/**
 * number of elements stored in vector
 */
size_t lvector_size(const lvector* vec);

/**
 * append element to end of vector, resizing if neccesary
 * 
 * @param vec vector to add to
 * @param val value to add
 */
void ivector_push_back(ivector* vec, int val);

/**
 * append element to end of vector, resizing if neccesary
 * 
 * @param vec vector to add to
 * @param val value to add
 */
void lvector_push_back(lvector* vec, long val);

/**
 * get element at given index
 * 
 * kills process if index is out of bounds
 */
int ivector_get(const ivector* vec, size_t index);

/**
 * get element at given index
 * 
 * kills process if index is out of bounds
 */
long lvector_get(const lvector* vec, size_t index);

/**
 * removes and returns final element in vector
 * 
 * kills process if index is out of bounds
 */
int ivector_pop_back(ivector* vec);

/**
 * removes and returns final element in vector
 * 
 * kills process if index is out of bounds
 */
long lvector_pop_back(lvector* vec);

/**
 * remove element at specified index and return it
 * 
 * kills process if index is out of bounds
 */
int ivector_remove(ivector* vec, size_t index);

/**
 * remove element at specified index and return it
 * 
 * kills process if index is out of bounds
 */
long lvector_remove(lvector* vec, size_t index);

/**
 * insert element into given index, moving back all elements behind it
 * 
 * kills process if index is out of bounds
 */
void ivector_insert(ivector* vec, int value, size_t index);

/**
 * insert element into given index, moving back all elements behind it
 * 
 * kills process if index is out of bounds
 */
void lvector_insert(lvector* vec, long value, size_t index);

#endif