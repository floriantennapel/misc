#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "heap.h"

#define MIN_SIZE 8

heap make_heap(int (*compare)(const void*, const void*), size_t datatype_size)
{
    heap ret;
    ret.cmp = compare;
    ret.datasize = datatype_size;
    ret.size = 0;
    ret.arr_cap = datatype_size * MIN_SIZE;

    ret.arr = malloc(ret.arr_cap);
    if (!ret.arr) {
        perror("make_heap:");
        exit(1);
    }

    return ret;
}

void heap_free(heap* h)
{
    free(h->arr);
}

size_t heap_size(const heap *h)
{
    return h->size;
}

void heap_push(heap* h, const void* value)
{
    if (h == NULL || value == NULL) {
        fprintf(stderr, "heap_push: NULL pointer\n");
        exit(1);
    }

    size_t t = h->datasize;

    // resizing array
    if (h->arr_cap < h->size * t + t) {
        h->arr_cap *= 2;
        h->arr = realloc(h->arr, h->arr_cap);
        if (!h->arr) {
            perror("heap_push:");
            exit(1);
        }
    }

    char* tmp[h->datasize];
    char* arr = h->arr;

    size_t ind = (h->size)++;
    memcpy(arr + ind * t, value, t);
    while (ind > 0) {
        size_t parent_ind = (ind - 1) / 2;
        void* current = arr + ind * t;
        void* parent = arr + parent_ind * t;

        if (h->cmp(current, parent) >= 0) {
            break;
        }

        memcpy(tmp, current, t);
        memcpy(current, parent, t);
        memcpy(parent, tmp, t);
        ind = parent_ind;
    }
}

void heap_pop(heap *h)
{
    if (h == NULL) {
        fprintf(stderr, "heap_pop: NULL pointer\n");
        exit(1);
    }
    if (h->size == 0) {
        fprintf(stderr, "heap_pop: empty heap\n");
        exit(1);
    }

    size_t t = h->datasize;
    void* arr = h->arr;
    char* tmp[t];
    memcpy(h->arr, h->arr + --(h->size) * t, t);

    size_t ind = 0;
    while (1) {
        size_t child_1_ind = 2 * ind + 1;
        size_t child_2_ind = child_1_ind + 1;
        void* child_1 = arr + child_1_ind * t;
        void* child_2 = arr + child_2_ind * t;
        void* current = arr + ind * t;

        if (child_1_ind >= h->size) {
            break;
        }

        size_t min_child_ind;
        void* min_child;
        if(h->cmp(child_1, child_2) <= 0) {
            min_child_ind = child_1_ind;
            min_child = child_1;
        } else {
            min_child_ind = child_2_ind;
            min_child = child_2;
        }

        if (h->cmp(current, min_child) > 0) {
            memcpy(tmp, current, t);
            memcpy(current, min_child, t);
            memcpy(min_child, tmp, t);
            ind = min_child_ind;
        } else {
            break;
        }
    }

    if (h->arr_cap / 2 >= MIN_SIZE * t && h->arr_cap < h->size * t / 2) {
        h->arr_cap /= 2;
        h->arr = realloc(h->arr, h->arr_cap);
        if (!h->arr) {
            perror("heap_pop:");
            exit(1);
        }
    }
}

void* heap_peek(const heap* h)
{
    if (h->size == 0) {
        fprintf(stderr, "heap_peek: empty heap\n");
        exit(1);
    }
    if (h == NULL) {
        fprintf(stderr, "heap_peek: NULL pointer\n");
        exit(1);
    }
    
    return h->arr;
}
