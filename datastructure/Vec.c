#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "Vec.h"

void checkAndgrow(Vec* vec) {
  if (vec->size == vec->capacity) {
    vec->capacity *= 2;
    vec->arr = realloc(vec->arr, sizeof(void*) * vec->capacity);
  }
}

void checkAndShrink(Vec* vec) {
  if (vec->size < vec->capacity / 2) {
    vec->capacity /= 2;
    vec->arr = realloc(vec->arr, sizeof(void*) * vec->capacity);
  }
}

void Vec_init(Vec* vec) {
  const int defaultSize = 8;

  vec->capacity = defaultSize;
  vec->size = 0;
  vec->arr = calloc(defaultSize, sizeof(void*));
}

void Vec_clear(Vec* vec) {
  for (Vec_size_t i = 0; i < vec->size; i++) {
    free(vec->arr[i]);
  }
  free(vec->arr);
}

Vec_size_t Vec_size(Vec* vec) {
  return vec->size;
}

void Vec_push(Vec* vec, void* val) {
  checkAndgrow(vec);

  vec->arr[vec->size] = val;
  ++(vec->size);
}

void* Vec_pop(Vec* vec) {
  if (!(vec->size)) {
    fprintf(stderr, "Vec is empty\n");
    return NULL;
  }

  --(vec->size);
  void* retval = vec->arr[vec->size];
  
  checkAndShrink(vec);
  return retval;
}

void* Vec_remove(Vec *vec, Vec_size_t index) {
  if (index >= vec->size) {
    fprintf(stderr, "Vec insert: index %llu out of bounds for size %llu\n", index, vec->size);
    return NULL;
  } else if (index == vec->size - 1) {
    return Vec_pop(vec);
  }

  void* retVal = vec->arr[index];
  --(vec->size);
  memmove(&(vec->arr[index]), &(vec->arr[index+1]), (vec->size - index) * sizeof(void*));

  checkAndShrink(vec);
  return retVal;
}

void Vec_insert(Vec *vec, void *val, Vec_size_t index) {
  checkAndgrow(vec);

  if (index >= vec->size) {
    fprintf(stderr, "Vec insert: index %llu out of bounds for size %llu\n", index, vec->size);
    exit(EXIT_FAILURE);
  }

  memmove(&(vec->arr[index+1]), &(vec->arr[index]), (vec->size - index) * sizeof(void*));
  vec->arr[index] = val;
  ++(vec->size);
}

void Vec_put(Vec *vec, void *val, Vec_size_t index) {
  if (index >= vec->size) {
    fprintf(stderr, "Vec insert: index %llu out of bounds for size %llu\n", index, vec->size);
    exit(EXIT_FAILURE);
  }

  vec->arr[index] = val;
}

void* Vec_get(Vec *vec, Vec_size_t index) {
  if (index >= vec->size) {
    fprintf(stderr, "Vec insert: index %llu out of bounds for size %llu\n", index, vec->size);
    return NULL;
  }
  
  return vec->arr[index];
}
