#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>

#define DECLARE_LIST(LIST_NAME, LIST_TYPE) \
    typedef struct \
    { \
        size_t capacity, size; \
        LIST_TYPE* arr; \
    } LIST_NAME; \
    \
    LIST_NAME LIST_NAME##_new(size_t capacity) \
    { \
        LIST_NAME ret = { .capacity = capacity, .size = 0 }; \
        if (!(ret.arr = malloc(capacity * sizeof(LIST_TYPE)))) { \
            perror(#LIST_NAME "_new, malloc"); \
            exit(1); \
        } \
        return ret; \
    } \
    \
    void LIST_NAME##_free(LIST_NAME* list) \
    { \
        if (list) \
            free(list->arr); \
    } \
    \
    size_t LIST_NAME##_size(const LIST_NAME* list) \
    { \
        if (!list) { \
            fprintf(stderr, #LIST_NAME "_size, list cannot be NULL\n"); \
            exit(1); \
        } \
        return list->size; \
    } \
    \
    const LIST_TYPE* LIST_NAME##_get(const LIST_NAME* list, size_t i) \
    { \
        if (!list) { \
            fprintf(stderr, #LIST_NAME "_get, list cannot be NULL\n"); \
            exit(1); \
        } \
        if (i < 0 || i >= list->size) { \
            fprintf(stderr, #LIST_NAME "_get, index out of bounds\n"); \
            exit(1); \
        } \
        return list->arr + i; \
    } \
    \
    void LIST_NAME##_push(LIST_NAME* list, LIST_TYPE val) \
    { \
        if (!list) { \
            fprintf(stderr, #LIST_NAME "_push, list is NULL\n"); \
            exit(1); \
        } \
        \
        if (list->size == list->capacity) { \
            list->capacity *= 2; \
            if (!(list->arr = realloc(list->arr, sizeof(LIST_TYPE) * list->capacity))) { \
                perror(#LIST_NAME "_push, realloc"); \
                exit(1); \
            } \
        } \
        list->arr[(list->size)++] = val; \
    } \
    \
    LIST_TYPE LIST_NAME##_pop(LIST_NAME* list) \
    { \
        if (!list) { \
            fprintf(stderr, #LIST_NAME "_pop, list is NULL\n"); \
            exit(1); \
        } \
        \
        if (!(list->size)) { \
            fprintf(stderr, #LIST_NAME "_pop, list is empty\n"); \
            exit(1); \
        } \
        LIST_TYPE ret = list->arr[--(list->size)]; \
        if (list->size < (list->capacity) / 2) { \
            list->capacity /= 2; \
            if (!(list->arr = realloc(list->arr, list->capacity * sizeof(LIST_TYPE)))) { \
                perror(#LIST_NAME "_pop, realloc"); \
                exit(1); \
            } \
        } \
        return ret; \
    }

#endif