#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#include "List.h"

typedef struct _node _node;

struct _node {
  void* val;
  _node* next;
};

struct _List {
  _node* head;
  uint64_t size;
};

List* List_init() {
  List* ll = malloc(sizeof(struct _List));
  if (!ll) {
    perror("");
    exit(1);
  }

  ll->head = NULL;
  ll->size = 0;

  return ll;
}

void List_deinit(List *list) {
  _node* node = list->head;
  _node* next;
  while (node) {
    next = node->next;
    free(node);
    node = next;
  }

  free(list);
}

void List_clear(List* list) {
  _node* node = list->head;
  _node* next;

  while (node) {
    next = node->next;
    free(node->val);
    free(node);
    node = next;
  }

  list->head = NULL;
  list->size = 0;
}

uint64_t List_size(List* list) {
  return list->size;
}

void List_push(List* list, void* val) {
  _node* new = malloc(sizeof(struct _node));
  if (!new) {
    perror("");
    exit(1);
  }

  ++(list->size);

  new->val = val;
  new->next = NULL;

  if (!(list->head)) {
    list->head = new; 
    return;
  } 

  _node* node = list->head;
  while (node->next) {
    node = node->next;
  }

  node->next = new;
}

void* List_pop(List* list) {
  if (!(list->head)) {
    fprintf(stderr, "List_pop: list is empty\n");
    return NULL;
  }

  _node* node = list->head;
  _node* prev = NULL;

  while (node->next) {
    prev = node;
    node = node->next;
  }

  void* retval = node->val;
  free(node);

  if (prev) {
    prev->next = NULL;
  } else {
    list->head = NULL;
  }

  --(list->size);
  return retval;
}

void* List_remove(List* list, uint64_t index) {
  uint64_t size = list->size;
  if (index >= size || index < 0) {
    fprintf(stderr, "List_remove: index %"PRIu64" out of bounds for size %"PRIu64"\n", index, size);
    return NULL;
  }

  if (index == size - 1) {
    return List_pop(list);
  }

  _node* prev = NULL;
  _node* node = list->head;
  for (uint64_t i = 0; i < index; i++) {
    prev = node;
    node = node->next;
  }

  void* retval = node->val;

  if (prev) {
    prev->next = node->next;
  } else {
    list->head = node->next;
  }

  free(node);
  --(list->size);

  return retval;
}

void List_insert(List* list, void* val, uint64_t index) {
  uint64_t size = list->size;
  if (index >= size || index < 0) {
    fprintf(stderr, "List_remove: index %"PRIu64" out of bounds for size %"PRIu64"\n", index, size);
    exit(1);
  }

  _node* new = malloc(sizeof(struct _node));
  if (!new) {
    perror("");
    exit(1);
  }

  new->val = val;

  _node* prev = NULL;
  _node* node = list->head;
  for (uint64_t i = 0; i < index; i++) {
    prev = node;
    node = node->next;
  }

  if (prev) {
    prev->next = new;
  } else {
    list->head = new;
  } 

  new->next = node;

  ++(list->size);
}

void List_put(List* list, void* val, uint64_t index) {
  uint64_t size = list->size;
  if (index >= size || index < 0) {
    fprintf(stderr, "List_remove: index %"PRIu64" out of bounds for size %"PRIu64"\n", index, size);
    exit(1);
  }

  _node* node = list->head;
  for (uint64_t i = 0; i < index; i++) {
    node = node->next;
  }

  node->val = val;
}


void* List_get(List* list, uint64_t index) {
  uint64_t size = list->size;
  if (index >= size || index < 0) {
    fprintf(stderr, "List_remove: index %"PRIu64" out of bounds for size %"PRIu64"\n", index, size);
    return NULL;
  }

  _node* node = list->head;
  for (uint64_t i = 0; i < index; i++) {
    node = node->next;
  }

  return node->val;
}
