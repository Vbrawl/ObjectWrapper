
#include "vector.h"
#include <stdlib.h>
#include <string.h>


OWObject_t* OWVector_Construct(size_t slot_steps) {
  OWObject_t* this = _OWObject_Construct(sizeof(OWVector_t), OWID_VECTOR, _OWVector_Destroy, NULL);
  OWVector_t* const obj = this->object;

  obj->array = NULL;
  obj->size = 0;
  obj->available_slots = 0;
  obj->slot_steps = slot_steps;
  OWVector_Resize(this, obj->slot_steps);
  return this;
}

int OWVector_Resize(OWObject_t* this, size_t slots) {
  this = OWObject_FindTypeInClass(this, OWID_VECTOR);
  if(this == NULL) {
    return -1;
  }
  OWVector_t* const obj = this->object;

  obj->array = realloc(obj->array, sizeof(void*) * slots);
  if(obj->array == NULL) return -2;
  obj->available_slots = slots;
  return 0;
}

int OWVector_PushBack(OWObject_t* this, void* item) {
  int error = 0;
  this = OWObject_FindTypeInClass(this, OWID_VECTOR);
  if(this == NULL) {
    return -1;
  }
  OWVector_t* const obj = this->object;

  if(obj->size + 1 > obj->available_slots) {
    error = OWVector_Resize(this, obj->available_slots + obj->slot_steps);
    if(error < 0) {
      return error;
    }
  }

  obj->array[obj->size] = item;
  obj->size += 1;
  return error;
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

  return obj->array[index];
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

  memmove(obj->array + index,
          obj->array + index + 1,
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

void* OWVector_PopBack(OWObject_t* this) {
  this = OWObject_FindTypeInClass(this, OWID_VECTOR);
  return OWVector_Pop(this, ((OWVector_t*)this->object)->size - 1);
}

void* OWVector_PopFront(OWObject_t* this) {
  return OWVector_Pop(this, 0);
}

void _OWVector_Destroy(OWObject_t* this) {
  OWVector_t* const obj = this->object;
  if(obj->array != NULL) {
    free(obj->array);
  }
}
