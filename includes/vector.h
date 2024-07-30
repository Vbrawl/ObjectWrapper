#ifndef DG_VECTOR_H
#define DG_VECTOR_H

#include "dg_object.h"


typedef struct Vector_struct {
  void* array;
  size_t size;
  size_t available_slots;
  size_t item_size;
  size_t slot_steps;
} Vector_t;

DGObject_t* Vector_Construct(size_t item_size, size_t slot_steps);
int Vector_Resize(DGObject_t* this, size_t slots);
int Vector_PushBack(DGObject_t* this, void* item);
void* Vector_Get(DGObject_t* this, size_t index);
void _Vector_Destroy(DGObject_t* this);
#define Vector_Destroy DGObject_Destroy


#endif
