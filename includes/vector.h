#ifndef OW_VECTOR_H
#define OW_VECTOR_H

#include "object.h"

enum OWVECTOR_INSERT_OPTION {
  OWVECTOR_INSERT_OPTION_INDEX  = 0,
  OWVECTOR_INSERT_OPTION_BACK   = -1,
  OWVECTOR_INSERT_OPTION_FRONT  = -2
};


typedef struct OWVector_struct {
  void** array;
  size_t size;
  size_t available_slots;
  size_t slot_steps;
} OWVector_t;

OWObject_t* OWVector_Construct(size_t slot_steps);
int OWVector_Resize(OWObject_t* this, size_t slots);
int _OWVector_Insert(OWObject_t* this, enum OWVECTOR_INSERT_OPTION option, size_t index, void* item);
#define OWVector_Insert(this, index, item) _OWVector_Insert(this, OWVECTOR_INSERT_OPTION_INDEX, index, item)
#define OWVector_PushBack(this, item) _OWVector_Insert(this, OWVECTOR_INSERT_OPTION_BACK, 0, item)
#define OWVector_PushFront(this, item) _OWVector_Insert(this, OWVECTOR_INSERT_OPTION_FRONT, 0, item)
#define OWVector_GetSize(this) ((OWVector_t*)OWObject_FindTypeInClass(this, OWID_VECTOR)->object)->size
void* OWVector_Get(OWObject_t* this, size_t index);
int OWVector_Remove(OWObject_t* this, size_t index);
void* OWVector_Pop(OWObject_t* this, size_t index);
#define OWVector_PopBack(this) OWVector_Pop(this, OWVector_GetSize(this) - 1)
#define OWVector_PopFront(this) OWVector_Pop(this, 0)
void _OWVector_Destroy(OWObject_t* this);
#define OWVector_Destroy OWObject_Destroy


#endif
