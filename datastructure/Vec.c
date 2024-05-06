#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "List.h"

struct _List {
  uint64_t capacity;
  uint64_t size;
  void** arr; 
};

static void checkAndGrow(List* list) {
  if (list->size == list->capacity) {
    list->capacity = list->capacity * 3 / 2;
    list->arr = realloc(list->arr, sizeof(void*) * list->capacity);
  }
}

static void checkAndShrink(List* list) {
  if (list->size < list->capacity * 2 / 3) {
    list->capacity = list->capacity * 2 / 3;
    list->arr = realloc(list->arr, sizeof(void*) * list->capacity);
  }
}

List* List_init() {
  const int defaultSize = 8;
  List* list = malloc(sizeof(struct _List));

  list->capacity = defaultSize;
  list->size = 0;
  list->arr = calloc(defaultSize, sizeof(void*));

  return list;
}

void List_deinit(List *list) {
  free(list->arr);
  free(list);
}

void List_clear(List* list) {
  for (uint64_t i = 0; i < list->size; i++) {
    free(list->arr[i]);
  }
  free(list->arr);

  list->arr = calloc(8, sizeof(void*));
  list->size = 0;
  list->capacity = 8;
}

uint64_t List_size(List *list) {
  return list->size;
}

void List_push(List* list, void* val) {
  checkAndGrow(list);

  list->arr[list->size] = val;
  ++(list->size);
}

void* List_pop(List* list) {
  if (!(list->size)) {
    fprintf(stderr, "List is empty\n");
    return NULL;
  }

  --(list->size);
  void* retval = list->arr[list->size];
  
  checkAndShrink(list);
  return retval;
}

void* List_remove(List *list, uint64_t index) {
  if (index >= list->size || index < 0) {
    fprintf(stderr, "List remove: index %"PRIu64" out of bounds for size %"PRIu64"\n", index, list->size);
    return NULL;
  } else if (index == list->size - 1) {
    return List_pop(list);
  }

  void* retVal = list->arr[index];
  --(list->size);
  memmove(&(list->arr[index]), &(list->arr[index+1]), (list->size - index) * sizeof(void*));

  checkAndShrink(list);
  return retVal;
}

void List_insert(List *list, void *val, uint64_t index) {
  checkAndGrow(list);

  if (index >= list->size || index < 0) {
    fprintf(stderr, "List insert: index %"PRIu64" out of bounds for size %"PRIu64"\n", index, list->size);
    exit(EXIT_FAILURE);
  }

  memmove(&(list->arr[index+1]), &(list->arr[index]), (list->size - index) * sizeof(void*));
  list->arr[index] = val;
  ++(list->size);
}

void List_put(List *list, void *val, uint64_t index) {
  if (index >= list->size || index < 0) {
    fprintf(stderr, "List put: index %"PRIu64" out of bounds for size %"PRIu64"\n", index, list->size);
    exit(EXIT_FAILURE);
  }

  list->arr[index] = val;
}

void* List_get(List *list, uint64_t index) {
  if (index >= list->size || index < 0) {
    fprintf(stderr, "List get: index %"PRIu64" out of bounds for size %"PRIu64"\n", index, list->size);
    return NULL;
  }
  
  return list->arr[index];
}
