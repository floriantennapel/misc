#ifndef __MAP_H__
#define __MAP_H__

/* implementation of a hashmap
 * example of use:
 *
 *
  #include <string.h>

  #include "Map.h"

  #define MAP_SIZE 97

  unsigned hashFunc(void* key) {
    return HASH_STR(key, MAP_SIZE);
  }

  int cmp(void* a, void* b) {
    return strcmp(a, b);
  }

  int main() {
    Map* map = Map_init(hashFunc, cmp, MAP_SIZE); 
    ...
  }
*/

struct _Map;
typedef struct _Map Map;

/** creates a new hashmap
 * @param hashFunc function used to hash the datatype used, value should be from 0 to size-1
 * @param cmp comparison function for comparing key values, must return 0 at equal
 * @param size A PRIME number, approximately the number of elements the map should hold 
 *
 * NOTE: since it is preferable that size is prime, any none prime sizes will be rejected */
Map* Map_init(unsigned (*hashFunc)(void* key), int (*cmp)(void* a, void* b), unsigned size);

/** free memory used by map, DOES NOT free contents 
 * ALL VALUES STORED IN MAP MUST BE FREE'D BEFORE CALLING THIS FUCNTION */
void Map_deinit(Map* map);

/** insert the value at the given key */
void Map_put(Map* map, void* key, void* val);

/** remove the entry at the given key
 * @return value for deallocation or NULL if no entry was found */
void* Map_remove(Map* map, void* key);

/** return value at given key, NULL if not entry was found */
void* Map_get(Map* map, void* key);

/** return value at given key, if no entry was found return the default */
void* Map_getOrDefault(Map* map, void* key, void* defaultVal);

/** simple hash function for strings
 * based on the polynomial rolling hash function with a prime factor of 31
 * forund here: https://algs4.cs.princeton.edu/34hash/
 * because of the different arguments, this function must be wrapped before it can be given to Map_init */
unsigned HASH_STR(char* key, unsigned size);
#endif 
