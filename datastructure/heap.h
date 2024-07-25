#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>

typedef struct heap 
{
    int (*cmp)(const void* a, const void* b); 
    size_t datasize;
    size_t size;
    size_t arr_cap;
    char* arr;
} heap;

/**
 * creates a new min-heap, must be free'd with heap_free after use
 *
 * @param compare comparison function, result must be < 0 if a < b, 0 if a == b and > 0 if a > b
 */
heap make_heap(int (*compare)(const void* a, const void* b), size_t datatype_size);

void heap_free(heap* h);

/**
 * number of elements stored in heap
 */
size_t heap_size(const heap* h);

/**
 * push value to heap
 *
 * @param value will be copied by value, so there are no lifetime requirements
 */
void heap_push(heap* h, const void* value);

/**
 * pop the smallest value off the heap
 *
 * to get the value, call heap_peek before popping
 */
void heap_pop(heap* h);

/**
 * return the smallest value in the heap, without popping
 */
void* heap_peek(const heap* h);

#endif
