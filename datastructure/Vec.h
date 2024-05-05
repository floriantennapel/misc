#ifndef Vec_h
#define Vec_h 

typedef unsigned long long Vec_size_t;

struct _Vec {
  Vec_size_t capacity;
  Vec_size_t size;
  void** arr; 
};

typedef struct _Vec Vec;

/** initialize a given vector */
void Vec_init(Vec* vec);

/** completely deallocate all values in Vec */
void Vec_clear(Vec* vec);

/** push a value to the end of the Vec */
void Vec_push(Vec* vec, void* val);

/** remove the value at the end 
 * @return NULL if Vec is empty, else pointer to value for deallocation */
void* Vec_pop(Vec* vec);

/** remove a value at the given index, shifting all succeeding values to the left 
 * @return NULL if Vec is empty, else pointer to value for deallocation */
void* Vec_remove(Vec* vec, Vec_size_t index);

/** insert a value at the given index, shifting all values behind to the right 
 * kills process on invalid index */
void Vec_insert(Vec* vec, void* val, Vec_size_t index);

/** change the value at a given index 
 * kills process on invalid index */
void Vec_put(Vec* vec, void* val, Vec_size_t index);

/** get the value at the given index 
 * @return NULL if Vec is empty, else pointer to value for deallocation */
void* Vec_get(Vec* vec, Vec_size_t index);
#endif
