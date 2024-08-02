
#include "vector.h"
#include <stdlib.h>
#include <string.h>


OWObject_t* OWVector_Construct(size_t slot_steps) {
  OWObject_t* array = OWArray_Construct(sizeof(void*), slot_steps);
  OWObject_t* this = _OWObject_Construct(sizeof(OWVector_t), OWID_VECTOR, NULL, array);
  OWVector_t* const obj = this->object;

  obj->size = 0;
  obj->slot_steps = slot_steps;
  return this;
}

int OWVector_Insert(OWObject_t* this, size_t index, void* item) {
  int error = 0;
  this = OWObject_FindTypeInClass(this, OWID_VECTOR);
  if(this == NULL) {
    return -1;
  }

  OWVector_t* const obj = this->object;
  if(index > obj->size) {
    return -2;
  }

  if(obj->size + 1 > OWArray_GetSlots(this)) {
    error = OWVector_Resize(this, OWArray_GetSlots(this) + obj->slot_steps);
    if(error < 0) {
      return error;
    }
  }

  if((obj->size > 0 || index > 0) && obj->size != index) {
    memmove(OWArray_GetBuffer(this) + (index + 1) * sizeof(void*),
            OWArray_GetBuffer(this) + index * sizeof(void*),
            (obj->size - index) * sizeof(void*));
  }
  OWArray_At(void*, this, index) = item;
  obj->size += 1;

  return 0;
}

void* OWVector_Get(OWObject_t* this, size_t index) {
  this = OWObject_FindTypeInClass(this, OWID_VECTOR);
  if(this == NULL) {
    return NULL;
  }
  OWVector_t* const obj = this->object;

  if(index >= obj->size) {
    return NULL;
  }

  return OWArray_At(void*, this, index);
}

int OWVector_Remove(OWObject_t* this, size_t index) {
  this = OWObject_FindTypeInClass(this, OWID_VECTOR);
  if(this == NULL) {
    return -1;
  }
  OWVector_t* const obj = this->object;

  if(index >= obj->size) {
    return -2;
  }

  memmove(OWArray_GetBuffer(this) + index * sizeof(void*),
          OWArray_GetBuffer(this) + (index + 1) * sizeof(void*),
          (obj->size - index) * sizeof(void*));
  obj->size -= 1;

  return 0;
}

void* OWVector_Pop(OWObject_t* this, size_t index) {
  this = OWObject_FindTypeInClass(this, OWID_VECTOR);

  void* item = OWVector_Get(this, index);
  OWVector_Remove(this, index);

  return item;
}
