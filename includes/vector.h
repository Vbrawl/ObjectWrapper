#ifndef OW_VECTOR_H
#define OW_VECTOR_H

#include "object.h"


typedef struct OWVector_struct {
  void** array;
  size_t size;
  size_t available_slots;
  size_t slot_steps;
} OWVector_t;

OWObject_t* OWVector_Construct(size_t slot_steps);
int OWVector_Resize(OWObject_t* this, size_t slots);
int OWVector_PushBack(OWObject_t* this, void* item);
void* OWVector_Get(OWObject_t* this, size_t index);
int OWVector_Remove(OWObject_t* this, size_t index);
void _OWVector_Destroy(OWObject_t* this);
#define OWVector_Destroy OWObject_Destroy


#endif
