#ifndef __List_h__
#define __List_h__

#include <stdint.h>

struct _List;
typedef struct _List List;

/** initializes and returns a heap allocated List */
List* List_init();

/** free memory used by List, not deallocating contents 
 * DO NOT USE BEFORE HAVING FREE'D CONTENTS */
void List_deinit(List* list);

/** completely deallocate contents of List and reset List to initial state */
void List_clear(List* list);

/** number of elements in List */
uint64_t List_size(List* list);

/** push a value to the end of the List */
void List_push(List* list, void* val);

/** remove the value at the end 
 * @return NULL if List is empty, else pointer to value for deallocation */
void* List_pop(List* list);

/** remove a value at the given index, shifting all succeeding values to the left 
 * @return NULL if List is empty, else pointer to value for deallocation */
void* List_remove(List* list, uint64_t index);

/** insert a value at the given index, shifting all values behind to the right 
 * kills process on invalid index */
void List_insert(List* list, void* val, uint64_t index);

/** change the value at a given index 
 * kills process on invalid index */
void List_put(List* list, void* val, uint64_t index);

/** get the value at the given index 
 * @return NULL if List is empty, else pointer to value for deallocation */
void* List_get(List* list, uint64_t index);
#endif
