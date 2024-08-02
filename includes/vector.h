#ifndef OW_VECTOR_H
#define OW_VECTOR_H

#include "object.h"
#include "array.h"


// Inherits OWArray_t
typedef struct OWVector_struct {
  size_t size;
  size_t slot_steps;
} OWVector_t;

OWObject_t* OWVector_Construct(size_t slot_steps);
#define OWVector_Resize OWArray_Resize
int OWVector_Insert(OWObject_t* this, size_t index, void* item);
#define OWVector_PushBack(this, item) OWVector_Insert(this, OWVector_GetSize(this), item)
#define OWVector_PushFront(this, item) OWVector_Insert(this, 0, item)
#define OWVector_GetSize(this) ((OWVector_t*)OWObject_FindTypeInClass(this, OWID_VECTOR)->object)->size
void* OWVector_Get(OWObject_t* this, size_t index);
int OWVector_Remove(OWObject_t* this, size_t index);
void* OWVector_Pop(OWObject_t* this, size_t index);
#define OWVector_PopBack(this) OWVector_Pop(this, OWVector_GetSize(this) - 1)
#define OWVector_PopFront(this) OWVector_Pop(this, 0)
#define OWVector_Destroy OWObject_Destroy


#endif
