#include <stdio.h>
#include <stdlib.h>

#include "Map.h"
#include "List.h"

struct _Map {
  unsigned size;
  unsigned (*hashFunc)(void* key);
  int (*cmp)(void* a, void* b);
  List** arr;
};

typedef struct _Pair {
  void* key;
  void* val;
} _Pair;

// given hash function should always give result from 0 to size-1,
// however, this function catches any times the function is wrong
static unsigned hash(Map* map, void* key) {
  return (map->hashFunc(key)) % map->size;
}

Map* Map_init(unsigned (*hashFunc)(void*), int (*cmp)(void* a, void* b), unsigned size) {
  for (int i = 2; i <= size / 2; i++) {
    if (size % i == 0) {
      fprintf(stderr, "Map_init: size must be a prime number\n");
      exit(1);
    }
  }

  Map* map = malloc(sizeof(struct _Map));
  if (!map) {
    perror("");
    exit(1);
  }

  map->size = size;
  map->arr = calloc(size, sizeof(List*));
  map->hashFunc = hashFunc;
  map->cmp = cmp;

  return map;
}

void Map_deinit(Map* map) {
  for (unsigned i = 0; i < map->size; i++) {
    List* collisionList = map->arr[i];
    if (collisionList) {
      List_clear(collisionList);
      List_deinit(collisionList);
    }
  } 
  
  free(map->arr);
  free(map);
}

void Map_put(Map* map, void* key, void* val) {
  unsigned index = hash(map, key);
  List* collisionList = map->arr[index];

  if (!collisionList) {
    map->arr[index] = List_init();
    _Pair* pair = malloc(sizeof(struct _Pair));
    if (!pair) {
      perror("");
      exit(1);
    }

    pair->val = val;
    pair->key = key;
    List_push(map->arr[index], pair);
  } else {
    for (int i = 0; i < List_size(collisionList); i++) {
      _Pair* listPair = List_get(collisionList, i);
      if (map->cmp(key, listPair->key) == 0) {
        listPair->val = val;
        return;
      }
    }

    _Pair* pair = malloc(sizeof(struct _Pair));
    if (!pair) {
      perror("");
      exit(1);
    }

    pair->val = val;
    pair->key = key;
    List_push(collisionList, pair);
  }
}

void* Map_remove(Map* map, void* key) {
  unsigned index = hash(map, key);
  List* collisionList = map->arr[index];

  if (!collisionList) {
    return NULL;
  }

  for (int i = 0; i < List_size(collisionList); i++) {
    _Pair* listPair = List_get(collisionList, i);
    if (map->cmp(key, listPair->key) == 0) {
      void* retval = listPair->val;
      free(List_remove(collisionList, i));

      if (!List_size(collisionList)) {
        List_deinit(collisionList);
        map->arr[index] = NULL;
      }

      return retval;
    }
  }

  return NULL;
}

void* Map_get(Map* map, void* key) {
  unsigned index = hash(map, key);
  List* collisionList = map->arr[index]; 

  if (!collisionList) {
    return NULL;
  }

  for (int i = 0; i < List_size(collisionList); i++) {
    _Pair* listPair = List_get(collisionList, i);
    
    if (map->cmp(key, listPair->key) == 0) {
      return listPair->val;
    }
  }

  return NULL;
}

void* Map_getOrDefault(Map* map, void* key, void* defaultVal) {
  void* result = Map_get(map, key);

  return result ? result : defaultVal;
}

unsigned HASH_STR(char* key, unsigned size) {
  unsigned hash = 0;
  const int R = 31;
  for (char* c = key; *c != '\0'; c++) {
    hash = (R * hash + *c) % size;
    printf("%u\n", hash);
  }

  return hash;
}
